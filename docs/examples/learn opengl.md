Recreating examples from [Learn OpenGL](https://learnopengl.com). Writing cleaner code instead of what I found on the site. Also modular examples that explore ideas in a different format. 
# showcases

## one 2D object in NDC

These objects do not use any model, view, or projection matrices in the shader. It simply draws a 2D object. Some of these objects include:
- triangles
- squares

These are also effectively drawn at the origin point. The coordinates still define positions, but these positions are based around the origin. So drawing the same object in different positions won't work. 

## multiple 2D objects transformed

These objects draw multiple 2D objects. These can be the same objects, with the same coordinates, but they are transformed in 2D space by applying a `model` matrix. Each object has the same `shader`,  `texture`, and `buffer` object passed as a reference for efficiency. Each object simply is transformed to different positions by applying this `model` matrix. 

## multiple 2D objects with camera

These objects are transformed in 2D space, but some objects are out of view. 
You can explore the world by using the `view` matrix. Each object has the same `view` matrix, but the `model` matrix gets updated. 

## 3D objects

Even the 2D objects can be 3D (they have x y and z coordinates, but z gets ignored). None of these objects "look" 3D. This is because by default OpenGL uses `orthographic projection`. This is the easiest projection to do. Objects that are far away do not get smaller, so essentially modifying the Z axis has no visible difference. 

To make 2D objects look 3D, we can use a `perspective projection`. This allows objects that are further away to get smaller, rather than stay the same size. So modifying the Z axis now has a visible difference. 

The standard object to draw in 3D is a rotating cube. This is easy to visualize in 3D while it is rotating. This can even be visualized with orthographic projection, so I will allow this first. 
