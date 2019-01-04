#include "GUI.h"






GUI::GUI()
{
	;
}


GUI::GUI(GLFWwindow * window, Map * map)
{
	//windowBounds;
	init(window, map);
}

void GUI::init(GLFWwindow * window, Map * map)
{

	this->map = map;
	map->tokens = &tokens;
	ctx = nk_glfw3_init(window, NK_GLFW3_INSTALL_CALLBACKS);
	/* Load Fonts: if none of these are loaded a default font will be used  */
	/* Load Cursor: if you uncomment cursor loading please hide the cursor */
	{struct nk_font_atlas *atlas;
	nk_glfw3_font_stash_begin(&atlas);
	/*struct nk_font *droid = nk_font_atlas_add_from_file(atlas, "../../../extra_font/DroidSans.ttf", 14, 0);*/
	/*struct nk_font *roboto = nk_font_atlas_add_from_file(atlas, "../../../extra_font/Roboto-Regular.ttf", 14, 0);*/
	/*struct nk_font *future = nk_font_atlas_add_from_file(atlas, "../../../extra_font/kenvector_future_thin.ttf", 13, 0);*/
	/*struct nk_font *clean = nk_font_atlas_add_from_file(atlas, "../../../extra_font/ProggyClean.ttf", 12, 0);*/
	/*struct nk_font *tiny = nk_font_atlas_add_from_file(atlas, "../../../extra_font/ProggyTiny.ttf", 10, 0);*/
	/*struct nk_font *cousine = nk_font_atlas_add_from_file(atlas, "../../../extra_font/Cousine-Regular.ttf", 13, 0);*/
	nk_glfw3_font_stash_end();
	/*nk_style_load_all_cursors(ctx, atlas->cursors);*/
	/*nk_style_set_font(ctx, &droid->handle);*/}

#ifdef INCLUDE_STYLE
	/*set_style(ctx, THEME_WHITE);*/
	/*set_style(ctx, THEME_RED);*/
	/*set_style(ctx, THEME_BLUE);*/
	/*set_style(ctx, THEME_DARK);*/
#endif

	bg.r = 0.10f, bg.g = 0.18f, bg.b = 0.24f, bg.a = 1.0f;
}

void GUI::draw()
{

	bounds.clear();

	nk_glfw3_new_frame();
	renderMenuBar();
	

	if (newMapWindow)
	{
		mainPanelInBackground = true;
		renderNewMap();
	}

	if (newObjectWindow)
	{
		mainPanelInBackground = true;
		renderNewObjectWindow();
	}

	
		if (nk_begin(ctx, map->getName().c_str(), nk_rect(0, 40, 240, SCREEN_HEIGHT), NK_WINDOW_BORDER  | NK_WINDOW_MINIMIZABLE) && !mainPanelInBackground)
		{

		

			struct nk_rect winRect = nk_window_get_bounds(ctx);
			bounds.push_back(Rect(winRect.x, winRect.y, winRect.w, winRect.h));
			enum { EASY, HARD };
			static int op = EASY;
			static int property = 20;
			nk_layout_row_begin(ctx, NK_STATIC, 50, 1);
			nk_layout_row_push(ctx, 80);
		

			nk_layout_row_push(ctx, 80);
			if (nk_button_label(ctx, "New Token"))
			{
				newObjectWindow = true;
			}
			

			nk_layout_row_static(ctx, 30, 210, 1);
			if (nk_combo_begin_text(ctx, "Tokens", 6, nk_vec2(nk_widget_width(ctx), 400)))
			{
				for (unsigned int i = 0; i < tokens.size(); i++)
				{
					int val = 25;
					struct nk_image img;
					img = nk_image_id((int)tokens[i].tex.ID);
					nk_layout_row_begin(ctx, NK_STATIC, 25, 3);
					nk_layout_row_push(ctx, 160);
					if (nk_selectable_image_text(ctx, img, tokens[i].name.c_str(), tokens[i].name.length(), NK_WINDOW_BORDER, &val))
					{
						map->selected_token = new Token();
						map->selected_token->name = tokens[i].name;
						map->selected_token->tex = tokens[i].tex;
					}
					nk_layout_row_push(ctx, 20);
					if (nk_button_label(ctx, "X"))
					{
						tokens.erase(tokens.begin() + i);
					}
				}
		
				nk_combo_end(ctx);
			}

			nk_layout_row_dynamic(ctx, 15, 1);
			nk_spacing(ctx, 1);

			nk_layout_row_begin(ctx, NK_STATIC, 30, 1);
			nk_layout_row_push(ctx, 120);
			if (nk_button_label(ctx, "Board BG"))
			{
				std::string tex = openTextureFile();
				std::string name = SplitFilename(tex);
				if (!ResourceManager::hasTexture(name) && tex != "")
				{
					ResourceManager::LoadTexture(tex.c_str(), true, name);
				}
				map->setBGTexture(ResourceManager::GetTexture(name));

			}
		}
		nk_end(ctx);
	
		windowBounds = bounds;
}


GUI::~GUI()
{
}

void GUI::renderMenuBar()
{
	if (nk_begin(ctx, "menu", nk_rect(0, 0, SCREEN_WIDTH, 40), NK_WINDOW_BORDER))
	{
		nk_menubar_begin(ctx);
		nk_layout_row_begin(ctx, NK_STATIC, 25, 5);
		nk_layout_row_push(ctx, 45);
		if (nk_menu_begin_label(ctx, "File", NK_TEXT_LEFT, nk_vec2(120, 200)))
		{
			nk_layout_row_static(ctx, 20, 40, 1);
			if (nk_menu_item_label(ctx,"New Map", NK_TEXT_LEFT))
			{
				newMapWindow = true;
			}

			nk_layout_row_static(ctx, 20, 40, 1);
			if (nk_menu_item_label(ctx, "Open", NK_TEXT_LEFT))
			{
			//Open	
			}
			nk_menu_end(ctx);
		}
		if (nk_menu_begin_label(ctx, "Edit", NK_TEXT_LEFT, nk_vec2(120, 200)))
		{
			nk_layout_row_static(ctx, 20, 40, 1);
			if (nk_menu_item_label(ctx, "Toggle Grid", NK_TEXT_LEFT))
			{
				if (map->readyToDraw())
					map->setGridRender(!map->getGridRender());
			}
			
			nk_menu_end(ctx);
		}

	
	}
	nk_end(ctx);
}


void GUI::renderNewMap()
{

	if (nk_begin(ctx, "New Map", nk_rect((SCREEN_WIDTH / 2) - 100, SCREEN_HEIGHT / 2 - 50, 400,220), NK_WINDOW_BORDER))
	{
		struct nk_rect winRect = nk_window_get_bounds(ctx);
		bounds.push_back(Rect(winRect.x, winRect.y, winRect.w, winRect.h));

		nk_layout_row_dynamic(ctx, 20, 1);
		nk_text(ctx, "Map Dimensions",14,NK_TEXT_LEFT);

		nk_layout_row_dynamic(ctx, 5, 1);
		nk_spacing(ctx, 1);
		nk_layout_row_begin(ctx, NK_STATIC, 25, 4);
		nk_layout_row_push(ctx, 50);
		nk_spacing(ctx, 1);
		nk_spacing(ctx, 1);
		nk_layout_row_push(ctx, 40);
		nk_text(ctx, "Name:", 5, NK_TEXT_LEFT);
		nk_layout_row_push(ctx, 75);
		nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD, mapnamebuff, sizeof(mapnamebuff) - 1, nk_filter_default);


		nk_spacing(ctx, 1);
		nk_layout_row_begin(ctx, NK_STATIC, 25, 6);
		nk_layout_row_push(ctx, 75);


		nk_layout_row_push(ctx, 40);
		nk_text(ctx, "X: ", 3, NK_TEXT_LEFT);
		nk_layout_row_push(ctx, 75);
		nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD, xbuff, sizeof(xbuff) - 1, nk_filter_decimal);
		nk_spacing(ctx, 1);
		nk_layout_row_push(ctx, 40);
		nk_text(ctx, "Y: ", 3, NK_TEXT_LEFT);
		nk_layout_row_push(ctx, 75);
		nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD, ybuff, sizeof(ybuff) - 1, nk_filter_decimal);


		nk_spacing(ctx, 1);
	
		nk_layout_row_begin(ctx, NK_STATIC, 30, 6);
		nk_layout_row_push(ctx, 50);
		nk_spacing(ctx, 1);
		if (nk_button_label(ctx, "OK"))
		{

		int x =	std::atoi(std::string(xbuff).c_str());
		int y = std::atoi(std::string(ybuff).c_str());


		std::string name = mapnamebuff;
		map->init(glm::ivec2(x / 5, y / 5));
		map->setName(std::string(mapnamebuff));

			mainPanelInBackground = false;
			newMapWindow = false;



			memset(xbuff, 0x00, sizeof xbuff);
			memset(ybuff, 0x00, sizeof ybuff);
			memset(mapnamebuff, 0x00, sizeof mapnamebuff);
		
		}
		nk_spacing(ctx, 1);
		nk_spacing(ctx, 1);
		nk_spacing(ctx, 1);
		if (nk_button_label(ctx, "Close"))
		{
			mainPanelInBackground = false;
			newMapWindow = false;
		}
	}
	nk_end(ctx);
}

void GUI::renderNewObjectWindow()
{
	if (nk_begin(ctx, "New Map", nk_rect((SCREEN_WIDTH / 2) - 100, SCREEN_HEIGHT / 2 - 50, 400, 220), NK_WINDOW_BORDER))
	{
		struct nk_rect winRect = nk_window_get_bounds(ctx);
		bounds.push_back(Rect(winRect.x, winRect.y, winRect.w, winRect.h));

		nk_layout_row_dynamic(ctx, 20, 1);
		nk_text(ctx, "New Token", 9, NK_TEXT_LEFT);

		nk_layout_row_dynamic(ctx, 5, 1);
		nk_spacing(ctx, 1);

		////////////////////////////////////////////////////////////////////
		nk_layout_row_begin(ctx, NK_STATIC, 25, 5);
		nk_layout_row_push(ctx, 50);

		nk_spacing(ctx, 1);

		nk_layout_row_push(ctx, 40);
		nk_text(ctx, "Name:", 5, NK_TEXT_LEFT);
		nk_layout_row_push(ctx, 80);
		nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD,objnamebuff, sizeof(objnamebuff) - 1, nk_filter_default);

		nk_spacing(ctx, 1);

		if (nk_button_label(ctx, "Load Image"))
		{
			std::string texture = openTextureFile();
			objStrTexName = SplitFilename(texture);
			memcpy(objTextureName, texture.c_str(), texture.size());
		}
		////////////////////////////////////////////////////////////////////
		nk_layout_row_begin(ctx, NK_STATIC, 25, 4);
		nk_layout_row_push(ctx, 50);

		nk_spacing(ctx, 1);

		nk_layout_row_push(ctx, 50 );
		nk_text(ctx, "Image: ", 7, NK_TEXT_LEFT);

		nk_layout_row_push(ctx, 200);
		const char * temp = objStrTexName.c_str();
		nk_text(ctx, temp, objStrTexName.length(), NK_TEXT_LEFT);

		nk_layout_row_push(ctx, 50);
		nk_spacing(ctx, 1);

		////////////////////////////////////////////////////////////////////

		nk_layout_row_begin(ctx, NK_STATIC, 30, 6);
		nk_layout_row_push(ctx, 50);
		nk_spacing(ctx, 1);

		if (nk_button_label(ctx, "OK"))
		{

		
			Token b;
	
			std::string name = SplitFilename(std::string(objTextureName));
			b.name = std::string(objnamebuff);
			if (b.name.size() != 0 && std::string(objTextureName) != "")
			{
				if (!ResourceManager::hasTexture(name));
					ResourceManager::LoadTexture(std::string(objTextureName).c_str(), true, name);

				
				b.tex = ResourceManager::GetTexture(name);


				tokens.push_back(b);
				memset(objTextureName, 0x00, sizeof objTextureName);
				memset(objnamebuff, 0x00, sizeof objnamebuff);
				objStrTexName = std::string();

				mainPanelInBackground = false;
				newObjectWindow = false;

			}
			else if(b.name.size() == 0)
			{
				MessageBox(NULL, "Name must have 1-20 characters", "Alert", MB_ICONASTERISK | MB_OK);
			}
			else
			{
				MessageBox(NULL, "Must have icon", "Alert", MB_ICONASTERISK | MB_OK);
			}
		}
		nk_spacing(ctx, 1);
		nk_spacing(ctx, 1);
		nk_spacing(ctx, 1);
		if (nk_button_label(ctx, "Close"))
		{
			memset(objTextureName, 0x00, sizeof objTextureName);
			memset(objnamebuff, 0x00, sizeof objnamebuff);
			objStrTexName = std::string();
			mainPanelInBackground = false;
			newObjectWindow = false;
		}
	}
	nk_end(ctx);
}

void GUI::renderNewBGObjectWindow()
{
}

void GUI::setUpBackgroundTexture()
{
}

void GUI::drawObjectInfoWindow()
{
}
