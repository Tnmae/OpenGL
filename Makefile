default:
	g++ -std=c++20 -o main glad/glad.c main.cpp shader.cpp VAO.cpp VBO.cpp EBO.cpp stb_image_imp.cpp Texture.cpp Camera.cpp Mesh.cpp Model.cpp Sphere.cpp `pkg-config --cflags --libs glfw3` `pkg-config --cflags --libs assimp`

clean:
	rm -f main
