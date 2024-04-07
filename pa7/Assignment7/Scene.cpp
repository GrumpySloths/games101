//
// Created by Göksu Güvendiren on 2019-05-14.
//

#include "Scene.hpp"

void Scene::buildBVH() {
    printf(" - Generating BVH...\n\n");
    this->bvh = new BVHAccel(objects, 1, BVHAccel::SplitMethod::NAIVE);
}

Intersection Scene::intersect(const Ray &ray) const {
    return this->bvh->Intersect(ray);
}

void Scene::sampleLight(Intersection &pos, float &pdf) const {
    float emit_area_sum = 0;
    for (uint32_t k = 0; k < objects.size(); ++k) {
        if (objects[k]->hasEmit()) {
            emit_area_sum += objects[k]->getArea();
        }
    }
    float p = get_random_float() * emit_area_sum;
    emit_area_sum = 0;
    for (uint32_t k = 0; k < objects.size(); ++k) {
        if (objects[k]->hasEmit()) {
            emit_area_sum += objects[k]->getArea();
            if (p <= emit_area_sum) {
                objects[k]->Sample(pos, pdf);
                break;
            }
        }
    }
}

bool Scene::trace(const Ray &ray, const std::vector<Object *> &objects,
                  float &tNear, uint32_t &index, Object **hitObject) {
    *hitObject = nullptr;
    for (uint32_t k = 0; k < objects.size(); ++k) {
        float tNearK = kInfinity;
        uint32_t indexK;
        Vector2f uvK;
        if (objects[k]->intersect(ray, tNearK, indexK) && tNearK < tNear) {
            *hitObject = objects[k];
            tNear = tNearK;
            index = indexK;
        }
    }

    return (*hitObject != nullptr);
}
Vector3f Scene::shade(Intersection &p, Vector3f &wo) const {
    Vector3f L_dir = Vector3f(0);
    Vector3f L_indir = Vector3f(0);
    // 对光线进行采样并生成碰撞检测光线
    Intersection pos_light = Intersection();
    float pdf_light = 0;
    sampleLight(pos_light, pdf_light);
    Vector3f lightDir = (pos_light.coords - p.coords).normalized();
    Ray ray_light = Ray(p.coords, lightDir);
    // 判断p点和light sample之间是否有障碍
    Intersection inter_light = intersect(ray_light);
    if (inter_light.happened && inter_light.coords == pos_light.coords) {
        // std::cout << "light sample" << std::endl;
        // 没有障碍下直接光照的处理
        Vector3f p2light = pos_light.coords - p.coords;
        float distance2 = dotProduct(p2light, p2light);
        L_dir = pos_light.emit * p.m->eval(wo, lightDir, p.normal) *
                fmax(0, dotProduct(lightDir, p.normal)) *
                fabs(dotProduct(lightDir, inter_light.normal)) / pdf_light /
                distance2;
    }
    float rand = get_random_float();
    if (rand < RussianRoulette) {
        // 递归继续存在下去的处理
        Vector3f wi = p.m->sample(wo, p.normal);
        Ray ray_sample = Ray(p.coords, wi);
        Intersection inter_sample = intersect(ray_sample);
        // 采样光线遇到散射物体的处理
        if (inter_sample.happened && !inter_sample.m->hasEmission()) {
            Vector3f wi_inverse = -wi;
            L_indir = shade(inter_sample, wi_inverse) *
                      p.m->eval(wo, wi, p.normal) *
                      fmax(0, dotProduct(wi, p.normal)) /
                      p.m->pdf(wo, wi, p.normal) / RussianRoulette;
        }
    }
    return L_dir + L_indir;
}

// Implementation of Path Tracing
Vector3f Scene::castRay(const Ray &ray, int depth) const {
    // TO DO Implement Path Tracing Algorithm here
    // 获取p点信息
    Intersection p = intersect(ray);
    Vector3f hitColor = this->backgroundColor;
    // 光线有碰撞到物体的处理
    if (p.happened) {
        if (p.m->hasEmission())
            return p.emit;
        else {
            Vector3f wo = -ray.direction;
            hitColor = shade(p, wo);
        }
        // std::cout << hitColor << std::endl;
    }

    return hitColor;
}