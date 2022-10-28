

# Процедурално генерирање на терен во бесконечност (Minecraft clone)

<p align="center">
  <img width="auto" height="400px" src="https://i.imgur.com/MHbhq01.jpg">
  <img width="auto" height="400px" src="https://i.imgur.com/aBpjVKn.jpg">
</p>

## References 

<p>[1] [OpenGL проект со основен код за организирање на мешови и модели.](https://github.com/Headturna/OpenGL-C---Tutorials) </p>
<p>[2] [Perlin Noise имплементација во C++](https://github.com/Reputeless/PerlinNoise) </p>
<p>[3] [Аудиториски вежби по Компјутерска графикa](https://github.com/joksim/OpenGLPrj) </p>
<p>[4] [Coding Minecraft in One Week - C++/OpenGL Programming Challenge](https://www.youtube.com/watch?v=Xq3isov6mZ8) </p>

# 1. Генерирање на меш (и терен)

За да го генерираме нашиот терен од воксели ќе користиме три-димензионален грид и според вредностите што ќе имаме во нашиот три-димензионален грид соодветно ќе поставиме коцки, кој ќе имаат иста големина и иста ротација. За да нацртаме обична коцка на екран е прилично едноставно.

   Primitives.cpp
                                          
    
    Cube::Cube() : Primitive() {
    
	   Vertex vertices[] =
		{
			//Position								//Color							//Texcoords					//Normals
			glm::vec3(-0.5f, 0.5f, 0.5f),			glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.f, 1.f),		glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(-0.5f, -0.5f, 0.5f),			glm::vec3(0.f, 1.f, 0.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(0.5f, -0.5f, 0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(0.5f, 0.5f, 0.5f),			glm::vec3(1.f, 1.f, 0.f),		glm::vec2(1.f, 1.f),		glm::vec3(0.f, 0.f, 1.f),

			glm::vec3(0.5f, 0.5f, -0.5f),			glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.f, 1.f),		glm::vec3(0.f, 0.f, -1.f),
			glm::vec3(0.5f, -0.5f, -0.5f),			glm::vec3(0.f, 1.f, 0.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, 0.f, -1.f),
			glm::vec3(-0.5f, -0.5f, -0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(0.f, 0.f, -1.f),
			glm::vec3(-0.5f, 0.5f, -0.5f),			glm::vec3(1.f, 1.f, 0.f),		glm::vec2(1.f, 1.f),		glm::vec3(0.f, 0.f, -1.f),

			glm::vec3(-0.5f, -0.5f, 0.5f),			glm::vec3(0.f, 1.f, 0.f),		glm::vec2(0.f, 1.f),		glm::vec3(0.f, -1.f, 0.f), // 1
			glm::vec3(0.5f, -0.5f, 0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 1.f),		glm::vec3(0.f, -1.f, 0.f), // 2
			glm::vec3(0.5f, -0.5f, -0.5f),			glm::vec3(0.f, 1.f, 0.f),		glm::vec2(1.f, 0.f),		glm::vec3(0.f, -1.f, 0.f),// 5
			glm::vec3(-0.5f, -0.5f, -0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, -1.f, 0.f),// 6

			glm::vec3(-0.5f, 0.5f, 0.5f),			glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.f, 1.f),		glm::vec3(0.f, 1.f, 0.f),  // 0 12
			glm::vec3(0.5f, 0.5f, 0.5f),			glm::vec3(1.f, 1.f, 0.f),		glm::vec2(1.f, 1.f),		glm::vec3(0.f, 1.f, 0.f),  // 3 13 
			glm::vec3(0.5f, 0.5f, -0.5f),			glm::vec3(1.f, 0.f, 0.f),		glm::vec2(1.f, 0.f),		glm::vec3(0.f, 1.f, 0.f), // 4 14
			glm::vec3(-0.5f, 0.5f, -0.5f),			glm::vec3(1.f, 1.f, 0.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, 1.f, 0.f), // 7 1

		};
	}


   <p align="center"> (Vertex-data на една коцка) </p>
   
   ****
   
   

    void Mesh::render(Shader* shader)
	{

		this->updateModelMatrix();

		//shader->use();
		
		shader->setMat4("model", ModelMatrix);
		

		//Bind VBO
		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
		//glBindVertexArray(this->VAO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));

		//Color
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));

		//Texcoord
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoord));

		//Normal
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));



		glDrawArrays(GL_TRIANGLES, 0, this->nrOfVertices);
	}

  
   <p align="center"> ( Draw функција на меш класта.) </p>
 
  ***
  Тука  функцијата е направена така што за секој mesh што ке се црта на екран ќе биде само подесен нов VBO, додека VOA го користиме истиот бидејќи секоја коцка ќе го користи истиот VOA. Преку Вертекс-дата ќе му ги поставуваме сите атрибути што му се потребни на секој voxel, на пример различна позицијаа со менување на Position точките, или пак кординатите на текстурата.

Најчесто во ваква Mesh класа би го сретнале спротивното, каде за секој нов меш што ќе се рендерира ќе се користи нов VOA, и со тоа ќе немаме потреба да се "бајндува" VBO  на секој draw-call, а атрибутите можеме да ги менуваме преку променливите на shader-ot.

## Chunks

   Но, ќе ни треба малце подобра организација на мешовите како и оптимизација. Ние не можеме да повикаме DrawCall на секоја коцка посебно што ја имаме во светот. На пример да земеме дека во секој момент ние имаме генерирано терен голем 32x32x32, тој содржи околу 32 768 воксели, тоа значи дека ќе треба во секој frame да повикаме Draw функцијата 32 768 пати.
   
   Затоа ќе користиме Chunks. Идеата е теренот-светот да го поделиме на повеќе делови. Секој дел ќе има фиксна големина, на пример 16х16х16. Потоа бидејќи коцките што ги цртаме се фиксни можеме да им ги земеме вредностите(vertex data) на сите коцки во еден дел и да ги унифицираме во еден голем меш. На тој начин во предходниот пример место да имаме 32 768 повици на GPU за рендерирање, ќе имаме 8.


    void Chunk::generateBlocks() {
		std::vector<Vertex> chunk_data;

		for (int x = 0; x < Chunk::LIMIT; x++) {
			for (int z = 0; z < Chunk::LIMIT; z++) {
				for (int y = 0; y < 32; y++) {

					glm::vec3 position = glm::vec3(x + getStartX(), y, z + getStartZ());
					BLOCK_TYPE blockType;
					std::bitset<6> sides;
					.
					.
					.
					// Spored pozicijata i vidot na voxel dobivame vertex-data za kocka na taa pozicija
					std::deque<Vertex> data = BlockData::getBlockData(sides, position, blockType);
					chunk_data.insert(chunk_data.end(), data.begin(), data.end());

				}
			}
		}
		
		// Generirame nov mesh za ovoj chunk so kombiniranje na mesh-data od sekoja kocka sto go sodrzhi 
		this->mesh = new Mesh(chunk_data.data(), chunk_data.size(), NULL, 0, glm::vec3(0.f, 0.f, 0.f),
			glm::vec3(0.f),
			glm::vec3(0.f),
			glm::vec3(1.f));
	}

## Endless map - Бесконечност во теренот

Бесконечноста е имплементирана на едноставен начин. Во секој момент имаме генерирано chunks околу играчот со радиус 3 chunks. Toa всушност испаѓа да биде 36 chunks генерирани во секој момент. Ако корисникот почне да се движи и ја смени позицијата од еден chunk во друг, тогаш некој од деловите се бришат(тие што се најдалеку од играчот) и на нивно место "градиме" нови полиња во насока каде што се движиме.

    void TileMap::CheckValidChunks(int playerX, int playerZ) {
		for (int i = 0; i < 36; i++) {

			if (chunks[i].isNull()) {
				continue;
			}

			if (chunks[i].getStartX() + Chunk::LIMIT * 3 < playerX) {
				//delete
				chunks[i].DeleteMesh();
				chunks[i] = GenerateMap(chunks[i].getStartX() + Chunk::LIMIT * 6, chunks[i].getStartZ());
				break;
			}
			if (chunks[i].getStartX() - Chunk::LIMIT* 3  > playerX) {
				//delete
				chunks[i].DeleteMesh();
				chunks[i] = GenerateMap(chunks[i].getStartX() - Chunk::LIMIT * 6, chunks[i].getStartZ());
				break;
			}
			if (chunks[i].getStartZ() + Chunk::LIMIT * 3 < playerZ) {
				//delete
				chunks[i].DeleteMesh();
				chunks[i] = GenerateMap(chunks[i].getStartX(), chunks[i].getStartZ() + Chunk::LIMIT * 6);
				break;
			}
			if (chunks[i].getStartZ() - Chunk::LIMIT * 3 > playerZ) {
				//delete
				chunks[i].DeleteMesh();
				chunks[i] = GenerateMap(chunks[i].getStartX(), chunks[i].getStartZ() - Chunk::LIMIT * 6);
				break;
			}

		}
	}







## Texture-Atlass
Место користење текстура за секој вид на коцка посебно, сите текстури се споени во еден Texture Atlass. Ова драстично ги подобрува перформансите на апликацијата бидејќи во update функцијата не треба да правиме менување (bind) на различна текстура за секоја коцка поединечно. Бидејќи ги знаеме големините на текстурите во него како и големината на Texture Atlass-от многу лесно можеме да ги одредиме кординатите на текстурата за секој меш (коцка).



<p align="center">
  <img width="auto" height="200px" src="https://i.imgur.com/joz6PQB.jpg">
</p>



		    // sheetWidth = goleminata na TextureAtlass
		    // spriteWidth = goleminata na edna tekstura vo Texture Atlass-ot
		    
		    glm::vec2 texCord = glm::vec2(cube.vertices[i].texcoord);
			texCord.x = ((x + texCord.x) * spriteWidth) / sheetWidth;
			texCord.y = ((y + texCord.y) * spriteWidth) / sheetWidth;

			cube.vertices[i].texcoord = texCord;


# 2. Perlin-Noise (генерирање на планини и реки)

<p align="center">
  <img width="auto" height="300px" src="https://i.imgur.com/aqeCQZu.png">
</p>

Perlin Noise е noise функција која, на некој начин создава “smooth randomness”. За овој проект јас веќе најдов готова имплементација на овои функции. Тие функционираат на следен начин: прима “seed” од кој генерира некој иницијални вредности, и потоа ние можеме да внесеме некоја вредност x и y, во нашиов случај позицијата на воксел во 2д простор, по должина и ширина. Потоа таа вредност што ќе ни ја даде функцијата всушност ни е висината на таа точка x,y. Ова го правиме за секоја позиција во теренот и на некој начин добиваме height map за нашиот терен. Од кога ја имаме оваа мапа на вредности многу лесно можеме да го исполниме теренот и во 3д простор со тоа што би ставиле воксел на секоја позиција што е под вредноста што ја добиваме од height мапата(од 0 до height_map[x][y]). За генерирање на уште по интересни вредности можеме да направиме комбинирање на noise функции со нивно собирање.
 <p align="center"> TileMap.cpp</p>

   
    double TileMap::noise(double nx, double ny) { 
		return perlin.noise2D_01(nx, ny) ;
	}

    double TileMap::ridgenoise(double nx, double ny) {
    	return 2 * (std::abs(perlin.noise2D_01(nx, ny)) );
    }

</br>

    Chunk TileMap::GenerateMap(int chunkX, int chunkZ) {
    	double value[16][16];

		std::vector< std::vector< std::vector<int> > > data;

		for (int y = 0; y < Chunk::LIMIT; y++) {

			std::vector< std::vector<int> > line;

			for (int x = 0; x < Chunk::LIMIT; x++) {

				double nx = (double)(x + (double)chunkZ ) / 16.0f,
					ny = (double)(y + (double)chunkX ) / 16.0f;

				double e0 = 1.2 * ridgenoise(1 * nx, 1 * ny);
				double  e1 = 0.6 * ridgenoise(2 * nx, 2 * ny) * e0;
				double e2 = 0.25 * ridgenoise(4 * nx, 4 * ny) * (e0 + e1);
				double e = (e0 + e1 + e2) / (1 + 0.5 + 0.25);
				e = std::pow(e, 3);

				value[y][x] = std::round(e * 24) / 24.0f + 1;
				...


По детален опис на генерирање на терен со Perlin Noise може да се види на следниот блог: [Making maps with noise functions](https://www.redblobgames.com/maps/terrain-from-noise/).
## Различни видови коцки
Според позицијата и висината што ја има коцка во светот, го добива и својот "вид" или type. Различните видови на коцки всушност имаат различни текстури. За да го направиме светот(теренот) по жив и да изгледа по природен воведуваме и различни видови на коцки, а тие се: 

 - Трева: што се поставува на почетокот на површина 
 - Земја: се поставува под површината
 - Камен: се поставува на повисоки површини и исто така 3 позиции пониско после површината 
 - Вода: се поставува над површина што има висина 2
 - Песок: се поставува околу поле со вода
 

 
 
 <div padding-top="25px"><p align="center"> TileMap.cpp</p></div>

	    // for every value in height map 
	    // we generate blocks vertically
	     
	    for (int i = 0; i < 32; i++) {
					if (i < value[y][x]) {
						if (i < value[y][x] - 2) {
							column.push_back(3); // stone
						}
						else { 
							if ((i + 1) >= value[y][x]) {
								column.push_back(1); // grass or sand
							}
							else {
								column.push_back(2); // dirt
							}
						}
					}
					else { // empty/ water
						if (i == 2) {
							column.push_back(-1); // water
						}
						else {
							column.push_back(0); // vazduh
						}
					}

		}

Преку BlockData класта се генерира посебни вертекс податоци за секоја коцка, со посебни атрибути:

    static std::deque<Vertex> getBlockData(std::bitset<6> sides, glm::vec3 position, BLOCK_TYPE blockType) {
		Cube cube = Cube();

		std::deque<Vertex> collection;

		//set position
		for (int i = 0; i < cube.vertices.size(); i++) {
			cube.vertices[i].position += position;

			if (blockType == WATER) {
				cube.vertices[i].position -= glm::vec3(0, 0.2f, 0);
			}
		}

		int x = blockType % 8, y = blockType / 8; // <- we get texPos from BlockType
		
		float spriteWidth = 32.0f;
		float sheetWidth = 256.0f;

		
		//set texCords
		for (int i = 0; i < cube.vertices.size(); i++) {
			glm::vec2 texCord = glm::vec2(cube.vertices[i].texcoord);
			texCord.x = ((x + texCord.x) * spriteWidth) / sheetWidth;
			texCord.y = ((y + texCord.y) * spriteWidth) / sheetWidth;

			cube.vertices[i].texcoord = texCord;
		}
		...

# 3. Кориснички инпут



Освен што има first person камера контроли имплементирано(логиката за камерата е земена од аудиториски вежби), има можност за поставување и уништување на коцка/воксел во теренот. Ова се постигнува со помош на по едноставена верзија од Raycasting. Кога корисникот ќе кликне ‚‚пукаме‘‘ ray во насока на каде гледа камерата со почеток на позицијата на камерата. Потоа проверуваме дали позицијата на ray-ot погодува дел/коцка во теренот. Ако има колизија, тогаш соодветно го бришеме вокселот од нашиот 3-димензионална листа или пак поставуваме нова коцка од страна каде дошол ray-от.
<p align="center">
  <img width="auto" height="300px" src="https://miro.medium.com/max/640/1*oXubxGtDjD6hXCi3VvDgxg.png">
</p>

<p align="center"> main.cpp</p>


    void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
	{
	    
	    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
	        glm::vec3 direction = camera.Front;

	        glm::vec3 start = camera.Position;


	        tileMap.checkClick(start, direction,0);
	        
	    }
	    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
	        glm::vec3 direction = camera.Front;

	        glm::vec3 start = camera.Position;


	        tileMap.checkClick(start, direction, 1);

	    }
	     
	}
<p align="center"> TileMap.cpp</p>
</br>

    void TileMap::checkClick(glm::vec3 start, glm::vec3 direction, int click) {
		glm::vec3 ray_pos = start;

		for (int i = 0; i < 10; i++) {
			ray_pos = ray_pos + direction;


			int x = std::round(ray_pos.x);
			int y = std::round(ray_pos.y);
			int z = std::round(ray_pos.z);

			Chunk* chunk =  getChunk(x, z);

			//chunk->getData(x, y, z);
			int x_chunk = x - chunk->getStartX();
			int z_chunk = z - chunk->getStartZ();

			if (chunk->getData(x_chunk, y, z_chunk) != 0) {

				if (click == 0) {
					chunk->deleteBlock(x_chunk, y, z_chunk);
					break;
				}
				else {

					glm::vec3 before = ray_pos - direction;
					x = std::round(before.x);
					y = std::round(before.y);
					z = std::round(before.z);

					x_chunk = x - chunk->getStartX();
					z_chunk = z - chunk->getStartZ();

					chunk->placeBlock(x_chunk, y, z_chunk);
					break;
				}


			}
		}
	}
Потоа од кога ќе направиме промена во делот(chunk), со тоа што сме избришале коцка или пак сме поставиле коцка, треба само одново да се изгради листата од вертекс дата, и пак да постават податоците во вертекс баферот(VBO).



