# GraphicsFinalProject
TJU 计算机图形技术 大作业

使用OpenGL实现了两个场景动画：阅兵式和兵马俑阵列，项目可以直接运行

## Dependencies
+ GLFW
+ GLAD
+ GLM
+ Windows x86

## 项目功能点
+ 实现了动画展示效果
+ 使用 shader pipeline 渲染画面
+ 为场景加入 phong 光照模型，具体包括：
  + 场景一的平行光模型
  + 场景二的手电筒聚光效果及平滑处理
+ 实现若干纹理贴图技术，具体包括
  + 使用 Cube Mapping 实现天空盒技术
  + 对场景二的墙面进行 bump mapping
+ 使用 Bezier 曲线控制物体运动路径
+ 使用 Bezier 曲面模拟飘动的国旗
+  使用天空盒技术构建场景背景
+  添加键盘和鼠标控制
