# 3d-Gaussian 研讨总结



## 3d Gaussian 缺点

1. 还是不够鲁棒，例如跑街景数据重建，对于大部分区域尤其是草丛，石子，屋顶其实很糊，可能是由于其基于gradient进行split或clone，还是纯手工的东西，需要对一些区域去调阈值
2. 过拟合特别严重，稍微偏一点视角效果就会很差，且也因此在做AIGC时会更加困难
3. 颜色显示精细度还远远不够强，希望将其融入到3D创作管线中去，Gaussian不用管mesh，其贴图由本身的颜色表示，虽然mip-Gaussian对这点有所改善，但离实际应用还有很长距离
4. 训练时间还是很长，对于实际大规模运用来说成本还是不够可控
5. 3D Gaussian为了效率问题还是有很多的近似,比如在渲染时没有考虑每个Gaussian之间的gaps关系
6. 对几何的建模比较模糊，不算非常精确的几何建模，例如Gaussian之间的相比位置关系就不是很清楚,提取几何会比较困难，对整个3D Gaussian的了解可能还是不够深入
7. Gaussian建模方法的artifact相比于nerf这类隐式方法更为严重，其训练到最后往往都是很扁的椭球，人眼对其很敏感,在分割后这个问题更为严重
8. 对于比较复杂的场景，Gaussian对超参会很敏感相较于nerf
9. 在训练完成后提取的点云过于散乱，并不是规整的分布在几何表面，导致几何信息难以利用
10. 要想对Gaussian进行simulaiton，往往需要很clean的data，而从现实数据中提取的往往很嘈杂，可能是由于其对相机参数很敏感

## 人体构建和场景构建之间的对比

1. 人体构建可能最好还是衣服，头,身体去分开构建，目前比较棘手的问题有做一个很好的talking head,因为会涉及到肤色，发型，许多微表情等，生成一个比较generate的model会比较困难，衣服问题比较大型的衣服数据集很难去访问
2. 场景更容易骗过眼睛，但场景更加多样，需要更泛化的模型,眼睛对人体artifact很敏感,可能需要更多专门的算法去人体局部进行特别优化
3. 人体和场景应该分别处理吗？还是当做同一对象对待
   > 人体所持的物体或衣物本身就包含大量场景特征，应该当做同一对象对待
4. 衣服(如各种样式及其变形)，头发都是数字人当前十分棘手的问题

## physical simulation(传统图形学) 与 AI

### 启发式思考

1. 一些diffusion model生成的视频已经可以capture一些物理性质了，在数据量足够大的情况下有没有可能直接基于现实中采集的图片去取代physical simulation
2. 有没有可能以 physical Gaussian为媒介去接入diffusion model去逐步替代physical simulation
3. 是否可以用physical constraint 来对模型训练进行约束来减少数据量需求
4. 能否用Gaussian重新构建 全局光照，raytracing这些传统方法来构建一个新的framework，如zbrush和Gaussian之间的结合
   
### 当前问题

一方面simualtion需要比较clean的数据，而真实世界获取的数据往往比较嘈杂。另一方面nerf和Gaussian这类建模往往只能capture表面，这在复杂变形如将物体拆分时会出现问题，其内部是空的，可能需要想办法填充使其内部看起来更加真实


## shape space 建模的思考-面向生成式模型

shape space的建模典型应用之一就是3d diffusion，而好的3d diffusion model需要一个高效的shape space，即每一个shape在shape space的underlying 表达在插值后重新恢复为shape，其仍然是合法的，这样可以用最少的3d shape去建模整个空间，当前做的最好的是sdf function，给定两个sdf function，其插值后再恢复为geometry仍然是合法的

## 3d表达要不要统一

应该是不会统一的，一方面采集设备多种多样并没有一个统一的格式，另一方面不同的3d 表达在pipeline中的作用是不一样的.
但不同形式之间信息无损的转换是很重要的



