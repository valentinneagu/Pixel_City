#include "Laborator9.h"
#include "Road.h"
#include "Building.h"

#include <vector>
#include <string>
#include <iostream>

#include <Core/Engine.h>

using namespace std;

//Map objects
Road *road;
Building *buildings;

//Arrays to stock textures for each type of building
std::vector<string> buildingTextures;
std::vector<string> towerTextures;


Laborator9::Laborator9()
{
}

Laborator9::~Laborator9()
{
}

void Laborator9::Init()
{
	const string textureLoc = "Source/Laboratoare/Laborator9/Textures/";

	// Load textures
	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "road.png").c_str(), GL_REPEAT);
		mapTextures["road"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "street.bmp").c_str(), GL_REPEAT);
		mapTextures["street"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "street2.bmp").c_str(), GL_REPEAT);
		mapTextures["street2"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "grass.tga").c_str(), GL_REPEAT);
		mapTextures["grass"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "building.jpeg").c_str(), GL_REPEAT);
		mapTextures["building"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "window.jpg").c_str(), GL_REPEAT);
		mapTextures["window"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "bricks.jpg").c_str(), GL_REPEAT);
		mapTextures["bricks"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "window2.jpg").c_str(), GL_REPEAT);
		mapTextures["window2"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "window4.jpg").c_str(), GL_REPEAT);
		mapTextures["window4"] = texture;
	}
	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "window6.jpg").c_str(), GL_REPEAT);
		mapTextures["window6"] = texture;
	}
	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "window7.jpg").c_str(), GL_REPEAT);
		mapTextures["window7"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "pixelcity.jpg").c_str(), GL_REPEAT);
		mapTextures["pixelcity"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "pixelcity2.jpg").c_str(), GL_REPEAT);
		mapTextures["pixelcity2"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "sky.jpg").c_str(), GL_REPEAT);
		mapTextures["sky"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "stop.jpg").c_str(), GL_REPEAT);
		mapTextures["stop"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "Moon.tga").c_str(), GL_REPEAT);
		mapTextures["moon"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "snowman.tga").c_str(), GL_REPEAT);
		mapTextures["snowman"] = texture;
	}

	// Create a simple quad
	{
		vector<glm::vec3> vertices
		{
			glm::vec3(1,   0, 1),	// Top Right
			glm::vec3(1,  0, 0),	// Bottom Right
			glm::vec3(0, 0, 0),	// Bottom Left
			glm::vec3(0,  0, 1),	// Top Left
		};

		vector<glm::vec3> normals
		{
			glm::vec3(0, 1, 1),
			glm::vec3(1, 0, 1),
			glm::vec3(1, 0, 0),
			glm::vec3(0, 1, 0)
		};

		// TODO : Complete texture coordinates for the square
		vector<glm::vec2> textureCoords
		{	
			glm::vec2(1.0f, 0.0f),
			glm::vec2(1.0f, 1.0f),
			glm::vec2(0.0f, 1.0f),
			glm::vec2(0.0f, 0.0f)
		};

		vector<unsigned short> indices =
		{
			0, 1, 3,
			1, 2, 3
		};

		Mesh* mesh = new Mesh("square");
		mesh->InitFromData(vertices, normals, textureCoords, indices);
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("box");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("cylinder");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "cylinder.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("sphere");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("stop");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "stop.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("snowman");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "Snowman.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	// Create a shader program for drawing face polygon with the color of the normal
	{
		Shader *shader = new Shader("ShaderLab9");
		shader->AddShader("Source/Laboratoare/Laborator9/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Laborator9/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	//Light & material properties
	{
		lightPosition = glm::vec3(0, 10, 0);
		materialShininess = 30;
		materialKd = 0.5;
		materialKs = 0.5;
	}

	/************************************************* ROAD ****************************************************************/
	road = new Road();
	buildings = new Building(road);

	//Set textures arrays
	//For each building a random texture will be picked
	buildingTextures.push_back("bricks");
	buildingTextures.push_back("building");
	buildingTextures.push_back("window4");
	buildingTextures.push_back("window6");
	buildingTextures.push_back("window7");
	buildingTextures.push_back("pixelcity2");

	towerTextures.push_back("building");
	towerTextures.push_back("pixelcity");
	towerTextures.push_back("pixelcity2");
}

void Laborator9::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);	
}

void Laborator9::Update(float deltaTimeSeconds)
{
	//################################# UPDATE #######################################################################
	for (int i = 0; i < road->getSize(); i++) {
		for (int j = 0; j < road->getSize(); j++) {		
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(i - road->getSize()/2, 0, j - road->getSize() / 2));
			if (road->getCoord(i, j) == 1) {
				if (road->getType(i, j) == 2) {
					//Render intersections
					RenderSimpleMesh(meshes["square"], shaders["ShaderLab9"], modelMatrix, mapTextures["road"]);
					if (road->numberOfNeighbours(i, j) == 4) {
						{
							glm::mat4 testMatrix = glm::mat4(1);
							testMatrix = glm::translate(testMatrix, glm::vec3(i - road->getSize() / 2, 0, j - road->getSize() / 2));
							testMatrix = glm::rotate(testMatrix, RADIANS(180.0f), glm::vec3(0, 1, 0));
							testMatrix = glm::scale(testMatrix, glm::vec3(0.005));
							RenderSimpleMesh(meshes["stop"], shaders["ShaderLab9"], testMatrix, mapTextures["stop"]);
						}
						{
							glm::mat4 testMatrix = glm::mat4(1);
							testMatrix = glm::translate(testMatrix, glm::vec3(i - road->getSize() / 2 + 1, 0, j - road->getSize() / 2 + 1));
							//testMatrix = glm::rotate(testMatrix, RADIANS(180.0f), glm::vec3(0, 1, 0));
							testMatrix = glm::scale(testMatrix, glm::vec3(0.005));
							RenderSimpleMesh(meshes["stop"], shaders["ShaderLab9"], testMatrix, mapTextures["stop"]);
						}
					}
				}
				else if(road->getType(i, j) == 0) {
					//Render vertical streets
					RenderSimpleMesh(meshes["square"], shaders["ShaderLab9"], modelMatrix, mapTextures["street"]);
				}
				else {
					//Render the horizontal streets
					RenderSimpleMesh(meshes["square"], shaders["ShaderLab9"], modelMatrix, mapTextures["street2"]);
				}
			}
			else {
				//Render grass to get a nice aspect
				RenderSimpleMesh(meshes["square"], shaders["ShaderLab9"], modelMatrix, mapTextures["grass"]);
			}

			//Render buildings
			if (road->getCoord(i, j) == 0) {

				//Square type buildings
				if (buildings->getType(i, j) == 0)
				{
					float scale = buildings->getScale(i, j);
					float height = 0.5 * scale;
					for (int l = 0; l < 3 * buildings->getLevel(i, j); l++) {
						
						if (l == 0) {
							//Put the first 3 levels the same to confer some heigth
							for (int m = 0; m < 2; m++)
							{
								glm::mat4 testMatrix = glm::mat4(1);
								testMatrix = glm::translate(testMatrix, glm::vec3(i - road->getSize() / 2 + 0.5, height, j - road->getSize() / 2 + 0.5));
								testMatrix = glm::scale(testMatrix, glm::vec3(scale));
								RenderSimpleMesh(meshes["box"], shaders["ShaderLab9"], testMatrix, mapTextures[buildingTextures[buildings->getTexture(i, j)]]);
								height += scale;
							}
						}
						glm::mat4 testMatrix = glm::mat4(1);
						testMatrix = glm::translate(testMatrix, glm::vec3(i - road->getSize() / 2 + 0.5, height, j - road->getSize() / 2 + 0.5));
						testMatrix = glm::scale(testMatrix, glm::vec3(scale));
						RenderSimpleMesh(meshes["box"], shaders["ShaderLab9"], testMatrix, mapTextures[buildingTextures[buildings->getTexture(i, j)]]);
						
						scale = scale * 0.8f;
						height += scale;
					}
				}

				//Cylinder type buildings
				if (buildings->getType(i, j) == 1)
				{
					float scale = 0.2f;
					float height = 0.8f;
					float initHeight = 0.8f;
					for (int l = 0; l < buildings->getLevel(i, j); l++) {
						glm::mat4 testMatrix = glm::mat4(1);
						testMatrix = glm::translate(testMatrix, glm::vec3(i - road->getSize() / 2 + 0.5, height, j - road->getSize() / 2 + 0.5));
						testMatrix = glm::rotate(testMatrix, RADIANS(90.0f), glm::vec3(1, 0, 0));
						testMatrix = glm::scale(testMatrix, glm::vec3(scale));
						RenderSimpleMesh(meshes["cylinder"], shaders["ShaderLab9"], testMatrix, mapTextures[buildingTextures[buildings->getTexture(i, j)]]);
						height += initHeight - 0.2;
					}
				}
			}

			if (road->getCoord(i, j) == 2) {
				{
					{
						glm::mat4 testMatrix = glm::mat4(1);
						testMatrix = glm::translate(testMatrix, glm::vec3(i - road->getSize() / 2 + 0.5, 0, j - road->getSize() / 2 + 0.5));
						testMatrix = glm::rotate(testMatrix, RADIANS(buildings->getScale(i, j)), glm::vec3(0, 1, 0));
						testMatrix = glm::scale(testMatrix, glm::vec3(0.2));
						RenderSimpleMesh(meshes["snowman"], shaders["ShaderLab9"], testMatrix, mapTextures["snowman"]);
					}
				}
			}
		}
	}

	{
		glm::mat4 testMatrix = glm::mat4(1);
		testMatrix = glm::translate(testMatrix, glm::vec3(0, 0, 0));
		//testMatrix = glm::rotate(testMatrix, RADIANS(90.0f), glm::vec3(1, 0, 0));
		testMatrix = glm::scale(testMatrix, glm::vec3(100));
		RenderSimpleMesh(meshes["sphere"], shaders["ShaderLab9"], testMatrix, mapTextures["sky"]);
	}
}

void Laborator9::FrameEnd()
{
	//DrawCoordinatSystem();
}

void Laborator9::RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 & modelMatrix, Texture2D* texture1, Texture2D* texture2)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	// render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	GLint light_position_uniform = glGetUniformLocation(shader->program, "light_position");
	glUniform3fv(light_position_uniform, 1, glm::value_ptr(lightPosition));

	// TODO: Set eye position (camera position) uniform
	glm::vec3 eyePosition = GetSceneCamera()->transform->GetWorldPosition();
	GLint eyePosition_uniform = glGetUniformLocation(shader->program, "eye_position");
	glUniform3fv(eyePosition_uniform, 1, glm::value_ptr(eyePosition));

	// TODO: Set material property uniforms (shininess, kd, ks, object color) 
	GLint shininess_uniform = glGetUniformLocation(shader->program, "material_shininess");
	glUniform1i(shininess_uniform, materialShininess);

	GLint kd_uniform = glGetUniformLocation(shader->program, "material_kd");
	glUniform1f(kd_uniform, materialKd);

	GLint ks_uniform = glGetUniformLocation(shader->program, "material_ks");
	glUniform1f(ks_uniform, materialKs);

	// Bind model matrix
	GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
	glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// Bind view matrix
	glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
	int loc_view_matrix = glGetUniformLocation(shader->program, "View");
	glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	// Bind projection matrix
	glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
	int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
	glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	if (texture1)
	{
		glUniform1i(glGetUniformLocation(shader->program, "textures"), 0);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1->GetTextureID());
		glUniform1i(glGetUniformLocation(shader->program, "texture_1"), 0);
	}

	if (texture2)
	{
		glUniform1i(glGetUniformLocation(shader->program, "textures"), 1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2->GetTextureID());
		glUniform1i(glGetUniformLocation(shader->program, "texture_2"), 1);
	}

	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}

Texture2D* Laborator9::CreateRandomTexture(unsigned int width, unsigned int height)
{
	GLuint textureID = 0;
	unsigned int channels = 3;
	unsigned int size = width * height * channels;
	unsigned char* data = new unsigned char[size];

	for (int i = 0; i < size; i++) {
		data[i] = rand();
	}

	glGenTextures(1, &textureID);
	// TODO: generate random texture data

	glBindTexture(GL_TEXTURE_2D, textureID);
	// Generate and bind the new texture ID

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // modul de wrapping pe orizontala
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // modul de wrapping pe verticala

	// TODO: Set the texture parameters (MIN_FILTER, MAG_FILTER and WRAPPING MODE) using glTexParameteri
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 4);

	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	CheckOpenGLError();

	// TODO: Use glTextImage2D to set the texture data
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	// TODO: Generate texture mip-maps
	glGenerateMipmap(GL_TEXTURE_2D);

	CheckOpenGLError();

	// Save the texture into a wrapper Texture2D class for using easier later during rendering phase
	Texture2D* texture = new Texture2D();
	texture->Init(textureID, width, height, channels);

	SAFE_FREE_ARRAY(data);
	return texture;
}

// Documentation for the input functions can be found in: "/Source/Core/Window/InputController.h" or
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/Window/InputController.h

void Laborator9::OnInputUpdate(float deltaTime, int mods)
{
	float speed = 2;

	if (!window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		glm::vec3 up = glm::vec3(0, 1, 0);
		glm::vec3 right = GetSceneCamera()->transform->GetLocalOXVector();
		glm::vec3 forward = GetSceneCamera()->transform->GetLocalOZVector();
		forward = glm::normalize(glm::vec3(forward.x, 0, forward.z));
	}
}

void Laborator9::OnKeyPress(int key, int mods)
{
	// add key press event
}

void Laborator9::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Laborator9::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
}

void Laborator9::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Laborator9::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Laborator9::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Laborator9::OnWindowResize(int width, int height)
{
}
