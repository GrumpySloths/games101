#include "rope.h"

#include <iostream>
#include <vector>

#include "CGL/vector2D.h"
#include "mass.h"
#include "spring.h"

namespace CGL {

    Rope::Rope(Vector2D start, Vector2D end, int num_nodes, float node_mass,
               float k, vector<int> pinned_nodes) {
        // TODO (Part 1): Create a rope starting at `start`, ending at `end`,
        // and containing `num_nodes` nodes.
        // 处理头结点
        Mass *head = new Mass(start, node_mass, false);
        masses.push_back(head);
        int n = num_nodes - 1;  // 弹簧的数量
        for (int i = 1; i < num_nodes; i++) {
            Mass *mass =
                new Mass((1 - (float)i / n) * start + (float)i / n * end,
                         node_mass, false);
            masses.push_back(mass);
            Spring *spring = new Spring(masses[i - 1], masses[i], k);
            springs.push_back(spring);
        }

        //        Comment-in this part when you implement the constructor
        for (auto &i : pinned_nodes) {
            masses[i]->pinned = true;
        }
    }

    void Rope::simulateEuler(float delta_t, Vector2D gravity) {
        float kd = 0.005;
        for (auto &s : springs) {
            // TODO (Part 2): Use Hooke's law to calculate the force on a node
            Vector2D v_ab = s->m2->position - s->m1->position;
            Vector2D v_ba = -v_ab;
            Vector2D f_ab = s->k * v_ab.unit() * (v_ab.norm() - s->rest_length);
            Vector2D fb = -kd *
                          dot(v_ab.unit(), s->m2->velocity - s->m1->velocity) *
                          v_ab.unit();
            Vector2D fa = -kd *
                          dot(v_ba.unit(), s->m1->velocity - s->m2->velocity) *
                          v_ba.unit();
            s->m1->forces += (f_ab + fa);
            s->m2->forces += (-f_ab + fb);
        }

        for (auto &m : masses) {
            if (!m->pinned) {
                // TODO (Part 2): Add the force due to gravity, then compute the
                // new velocity and position
                m->forces += (gravity - m->velocity * kd);

                Vector2D a = m->forces / m->mass;
                m->velocity += a * delta_t;
                m->position += m->velocity * delta_t;
                // TODO (Part 2): Add global damping
            }

            // Reset all forces on each mass
            m->forces = Vector2D(0, 0);
        }
    }

    void Rope::simulateVerlet(float delta_t, Vector2D gravity) {
        float dampingfactor = 0.00005;
        for (auto &s : springs) {
            // TODO (Part 3): Simulate one timestep of the rope using explicit
            // Verlet （solving constraints)
            Vector2D v_ab = s->m2->position - s->m1->position;
            Vector2D x_ab = v_ab.unit() * (v_ab.norm() - s->rest_length) / 2;
            if (!s->m1->pinned) {
                s->m1->position += x_ab;
                s->m2->position -= x_ab;
            } else {
                s->m2->position -= 2 * x_ab;
            }
            // if (!s->m2->pinned)
            //     s->m2->position -= x_ab;
        }

        for (auto &m : masses) {
            if (!m->pinned) {
                Vector2D temp_position = m->position;
                // TODO (Part 3.1): Set the new position of the rope mass
                Vector2D a = gravity / m->mass;
                // m->position += ((temp_position - m->last_position) +
                //                 a * delta_t * delta_t);

                // TODO (Part 4): Add global Verlet damping
                m->position +=
                    ((1 - dampingfactor) * (temp_position - m->last_position) +
                     a * delta_t * delta_t);
                m->last_position = temp_position;
            }
        }
    }
}  // namespace CGL
