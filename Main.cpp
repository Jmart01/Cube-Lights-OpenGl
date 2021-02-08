#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <shader.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stbi_Image.h>
#include <Camera.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

Camera camera;
void CursorMoved(GLFWwindow* inWindow, double xPos, double yPos) 
{
	camera.CursorMoved(xPos, yPos);
}

std::string GetSourcString(const std::string& Dir)
{
	std::ifstream SourceFile{ Dir };
	std::ifstream ShaderIF{Dir};
	std::string ShaderSrcString;
	std::string Read;
	while (std::getline(ShaderIF, Read))
	{
		ShaderSrcString += Read;
		ShaderSrcString += '\n';
	}

	return ShaderSrcString;
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH,WINDOW_HEIGHT,"OpenGLDrawTriangle",nullptr,nullptr);
	glfwMakeContextCurrent(window);
	camera.SetWindow(window);
	gladLoadGLLoader(GLADloadproc(glfwGetProcAddress));

	float vertices[] = 
	{		//VERTICES			UVs				normals
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,   0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,   0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,   0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,   0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,   0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,   0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,   0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,   0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,   0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,   0.0f,  0.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,   0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,   0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,   -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,   -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,   -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,   -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,   -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,   -1.0f,  0.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,    1.0f, 0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,    1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,    1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,    1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,    1.0f, 0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,    1.0f, 0.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,     0.0f, -1.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,     0.0f, -1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,     0.0f, -1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,     0.0f, -1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,     0.0f, -1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,     0.0f, -1.0f, 0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,      0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,      0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,      0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,      0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,      0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,      0.0f,  1.0f,  0.0f
	};

	shader VertexShader("Resources/Shaders/VertexShader.shader", GL_VERTEX_SHADER);
	shader FragShader("Resources/Shaders/FragmentShader.shader", GL_FRAGMENT_SHADER);
	
	int success = false;
	glGetShaderiv(VertexShader.GetShaderID(), GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char ComplieMessage[512];
		glGetShaderInfoLog(VertexShader.GetShaderID(), 512, nullptr, ComplieMessage);
		std::cout << "compile error: " << ComplieMessage << std::endl;
	}
	/*const char* VertexSrcRaw = VertexShaderSrcStr.c_str();
	unsigned int VertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VertexShader, 1, &VertexSrcRaw, nullptr);
	glCompileShader(VertexShader);

	const char* FragmentSrcRaw = FragmentShaderSrcStr.c_str();
	unsigned int FragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragShader, 1, &FragmentSrcRaw, nullptr);
	glCompileShader(FragShader);
	*/
	unsigned int Program = glCreateProgram();
	glAttachShader(Program, VertexShader.GetShaderID());
	glAttachShader(Program, FragShader.GetShaderID());
	glLinkProgram(Program);
	glUseProgram(Program);
	glDeleteShader(VertexShader.GetShaderID());
	glDeleteShader(FragShader.GetShaderID());

	int LinkSuccess = false;
	glGetProgramiv(Program, GL_LINK_STATUS, &LinkSuccess);
	if (!LinkSuccess)
	{
		std::cout << "linking error" << std::endl;
	}
	
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,GL_STATIC_DRAW);
	//telling vbo the location 0 is 3 floats
	glVertexAttribPointer(0, 3 , GL_FLOAT, GL_FALSE, sizeof(float)*8,(void*)0);
	//another location of the number 1 has 2 floats
	glVertexAttribPointer(1, 2 , GL_FLOAT, GL_FALSE, sizeof(float)*8 , (void*)(sizeof(float)*3));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 5));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	unsigned int texture;
	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	int width, height, comp;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load("Resources/Textures/pika.jpg.jpg", &width, &height, &comp,0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

	}
	stbi_image_free(data);
	int TextureLoc = glGetUniformLocation(Program, "Texture");
	glUniform1i(TextureLoc, 0);


	glm::mat4 ModelMatrix(1.f);
	int modelMatrixLoc = glGetUniformLocation(Program, "ModelMatrix");
	ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0.f, 0.f, -3.f));
	float RotateSpeed = 50.f;
	float previousTime = glfwGetTime();
	glEnable(GL_DEPTH_TEST);
	
	float AspectRatio = (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT;
	glm::mat4 Projectionmatrix = glm::perspective(glm::radians(45.f), AspectRatio, 0.01f, 1000.f);
	int ProjectionmatrixLoc = glGetUniformLocation(Program, "Projectmatrix");

	
	int ViewMatrixLoc = glGetUniformLocation(Program, "ViewMatrix");

	glfwSetCursorPosCallback(window, CursorMoved);
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	IMGUI_CHECKVERSION();
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui::StyleColorsDark();
	ImGui_ImplOpenGL3_Init((char*)glGetString(330));

	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	glm::vec3 LightLocation(2.f, 2.f, 2.f);
	unsigned int LightLocLocation = glGetUniformLocation(Program, "LightLoc");
	glUniform3fv(LightLocLocation, 1, glm::value_ptr(LightLocation));

	float colors[3] = { 2.f,2.f,2.f };
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	bool cursorLocked = true;
	
	while (!glfwWindowShouldClose(window))
	{
		float  DeltaTime = glfwGetTime() - previousTime;
		previousTime = glfwGetTime();
		glClearColor(0.6f, 0.4f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//glm::vec3 offset(0.f, 0.f, 0.f);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		
		camera.Update(DeltaTime,cursorLocked);

		ModelMatrix = glm::rotate(ModelMatrix, glm::radians(RotateSpeed * DeltaTime), glm::vec3(1.f, 1.f, 1.f));

		glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(ModelMatrix));

		glUniformMatrix4fv(ProjectionmatrixLoc, 1, GL_FALSE, glm::value_ptr(Projectionmatrix));

		glUniformMatrix4fv(ViewMatrixLoc, 1, GL_FALSE, glm::value_ptr(camera.GetViewMatrix()));
		glDrawArrays(GL_TRIANGLES, 0, 12*3);

		static float f = 0;
		static int counter = 0;

		ImGui::Begin("Hello, world!");
		ImGui::ColorEdit3("Color For Light", colors);

		glm::vec3 lightColor(colors[0], colors[1], colors[2]);
		unsigned int lightColorLoc = glGetUniformLocation(Program, "LightColorLoc");
		glUniform3fv(lightColorLoc, 1, glm::value_ptr(lightColor));

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

		ImGui::End();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	//glfwTerminate();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
	return 0;
}