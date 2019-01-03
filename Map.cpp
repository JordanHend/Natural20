#include "Map.h"




bool dragMap = true;
void Map::draw()
{
	if (readyToDraw())
	{
		
	

		Shader s = ResourceManager::GetShader("sprite");
		s.use();
		s.setMat4("view", camera.getViewMatrix());
		projection = glm::ortho(0.0f, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, 0.0f, -1.0f, 1.0f);
		s.setMat4("projection", projection);
		s.setFloat("scale", scale);


		if (bginitialized)
		{
			renderer->DrawSprite(BGIMAGE, glm::vec2(0, 0), glm::vec2(bounds.x * 50, bounds.y * 50));
		}


		for (unsigned int i = 0; i < objects.size(); i++)
		{
			renderer->DrawSprite(objects[i].tex, objects[i].pos, glm::vec2(50));
			dFont.RenderText("X", objects[i].pos.x + 20, objects[i].pos.y, 0.2  * scale, glm::vec3(0));
		}

		if (shouldDrawGrid)
			drawGrid();


		if (selected_token != NULL)
		{
			dragMap = false;
			s.use();
		
			
			s.setMat4("view", glm::mat4(1));
			float tscale = scale;
			scale = 1;
			renderer->DrawSprite(selected_token->tex, glm::vec2((lastX - 25),(lastY - 25)), glm::vec2(40 , 40));
			scale = tscale;
		}
	}
}

void Map::logic()
{
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE && selected_token != NULL)
	{

		for (unsigned int i = 0; i < logicalGrid.size(); i++)
		{
			Rect r = logicalGrid[i];
			glm::vec2 temp = r.getPos();

			glm::vec4 temp2 = glm::vec4(temp, 1, 1);





			glm::mat4 model(1);
			model = glm::scale(glm::vec3(scale));
			glm::mat4 view = camera.getViewMatrix();
			temp2 = view * model * temp2;
			r.setPos(glm::vec2(temp2.x, temp2.y));
			r.w = r.w * scale;
			r.h = r.h * scale;



			if (r.mouseOver(glm::vec2(lastX, lastY)))
			{
				Object b;
				b.name = selected_token->name;
				b.tex = selected_token->tex;
				b.pos = temp;
				objects.push_back(b);
			}
		}

		selected_token = NULL;
		dragMap = true;
	}




}

void Map::init(glm::ivec2 bounds, TextureRenderer * rend)
{
	
	shouldDrawGrid = true;
	if(rend != NULL)
	this->renderer = rend;

	this->bounds = bounds;

	if (gridSetup)
	deleteGrid();





}


void Map::deleteGrid()
{
	glDeleteVertexArrays(1, &gridVAO);
	glDeleteBuffers(1, &gridVBO);
}

void Map::drawGrid()
{
	std::vector<glm::vec2> outline;
	if (!gridSetup)
	{
		float tx = bounds.x * 50, ty = bounds.y * 50;
		float step = 50;
		int xlength = bounds.x + 1;
		int ylength = bounds.y + 1;

		logicalGrid.resize(bounds.x * bounds.y);
		int t0y = 0;
		for (unsigned int i = 0; i < bounds.x * bounds.y; i++)
		{
			logicalGrid[i] = Rect((i * (int)step) % (bounds.x * (int)step), t0y, 50, 50);
			if (((i + 1) * (int)step) % (bounds.x * (int)step) == 0 && i != 0)
				t0y += 50;
		}

		for (unsigned int i = 0; i < logicalGrid.size(); i++)
		{
			Rect r = logicalGrid[i];
			outline.push_back(glm::vec2(r.x, r.y));
			outline.push_back(glm::vec2(r.x, r.y + r.h));

			outline.push_back(glm::vec2(r.x, r.y));
			outline.push_back(glm::vec2(r.x + r.w, r.y));

			outline.push_back(glm::vec2(r.x + r.w, r.y));
			outline.push_back(glm::vec2(r.x + r.w, r.y + r.h));

			outline.push_back(glm::vec2(r.x, r.y + r.h));
			outline.push_back(glm::vec2(r.x + r.w, r.y + r.h));
		}


	

		glGenBuffers(1, &gridVBO);
		glGenVertexArrays(1, &gridVAO);
		glBindVertexArray(gridVAO);
		glBindBuffer(GL_ARRAY_BUFFER, gridVBO);
		glBufferData(GL_ARRAY_BUFFER, outline.size() * sizeof(glm::vec2), &outline[0], GL_STATIC_DRAW);
		// position attribute
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);
		glEnableVertexAttribArray(0);

		glBindVertexArray(0);
		numLines = outline.size();
		gridSetup = true;
	}
	Shader s = ResourceManager::GetShader("grid");
	s.use();
	projection = glm::ortho(0.0f, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, 0.0f, -1.0f, 1.0f);
	s.setFloat("scale", scale);
	glm::mat4 model(1.0f);
	model = glm::scale(model, glm::vec3(scale));
	s.setMat4("model", model);
	s.setMat4("view", camera.getViewMatrix());
	s.setMat4("projection", projection);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBindVertexArray(gridVAO);
	glDrawArrays(GL_LINES, 0, numLines);
	glBindVertexArray(0);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		//std::cout << "GL ERROR! " << err << std::endl;
	}
}



Map::~Map()
{
	renderer = NULL;
}