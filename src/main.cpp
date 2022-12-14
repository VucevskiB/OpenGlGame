#include <OpenGLPrj.hpp>

#include <GLFW/glfw3.h>

#include <Camera.hpp>
#include <Shader.hpp>
#include <Block.hpp>

#include <iostream>
#include <string>
#include <vector>

const std::string program_name = ("OpenGL voxel terrain generation project");

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
unsigned int loadTexture(char const *);
void draw(Shader shader, GLFWwindow* window,int texture);


// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
static Camera camera(glm::vec3(0.0f, 20, 0));
static float lastX = SCR_WIDTH / 2.0f;
static float lastY = SCR_HEIGHT / 2.0f;
static bool firstMouse = true;



// timing
static float deltaTime = 0.0f;
static float lastFrame = 0.0f;

// lighting
static glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

//Game Objects
TileMap tileMap = TileMap();



int main() {
  // glfw: initialize and configure
  // ------------------------------
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(
      GLFW_OPENGL_FORWARD_COMPAT,
      GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

  // glfw window creation
  // --------------------
  GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT,
                                        program_name.c_str(), nullptr, nullptr);
  if (window == nullptr) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  glfwSetCursorPosCallback(window, mouse_callback);
  glfwSetScrollCallback(window, scroll_callback);
  glfwSetMouseButtonCallback(window, mouse_button_callback);

  // tell GLFW to capture our mouse
  // 
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  // glad: load all OpenGL function pointers
  // ---------------------------------------
  if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  // configure global opengl state
  // -----------------------------
  glEnable(GL_DEPTH_TEST);

  //glEnable(GL_CULL_FACE);
  //glCullFace(GL_FRONT);
  glEnable(GL_BLEND);
  glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);



  // build and compile our shader program
  // ------------------------------------
  std::string shader_location("../res/shaders/");
  std::string texture_location("../res/textures/");

  std::string block_shader("block");
  std::string skybox_shader("skybox");

  // build and compile our shader zprogram
  // ------------------------------------
  Shader blockShader(
      shader_location + block_shader + std::string(".vert"),
      shader_location + block_shader + std::string(".frag"));

  Shader skyboxShader(
      shader_location + skybox_shader + std::string(".vert"),
      shader_location + skybox_shader + std::string(".frag"));


  // load textures (we now use a utility function to keep the code more
  // organized)
  // -----------------------------------------------------------------------------

  unsigned int textureAtlas =
      loadTexture((texture_location + "textureAtlass.png").c_str());


  std::vector<std::string> faces
  {
      texture_location + "skybox/" + "right.jpg",
      texture_location + "skybox/"+ "left.jpg",
      texture_location + "skybox/" + "top.jpg",
      texture_location + "skybox/" + "bottom.jpg",
      texture_location + "skybox/" + "front.jpg",
      texture_location + "skybox/" + "back.jpg"
  };
  Skybox skybox = Skybox(faces, skyboxShader);
  // shader configuration
  // --------------------
  blockShader.use();
  blockShader.setInt("texture1", 0);

  tileMap.SetShader(textureAtlas, blockShader);

  tileMap.InitChunks();



  // render loop
  // -----------
  while (!glfwWindowShouldClose(window)) {
    // per-frame time logic
    // --------------------
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;

    //render
    if (deltaTime >= 1 / 60) {
        lastFrame = currentFrame;

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //_______________
        //Draw Skybox
        // view/projection transformations
        

        glm::mat4 projection =
            glm::perspective(glm::radians(camera.Zoom),
                (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = glm::mat4(glm::mat3(camera.GetViewMatrix()));

        skybox.Draw(projection, view);

        //___________
        //Draw TileMap Chunks
        draw(blockShader,window, textureAtlas); // tileMap


        glUseProgram(0);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //update
    tileMap.CheckValidChunks(camera.Position.x, camera.Position.z);

    // input
    // -----
    processInput(window);

  }

  // optional: de-allocate all resources once they've outlived their purpose:
  // ------------------------------------------------------------------------
  tileMap.ReleaseData();

  // glfw: terminate, clearing all previously allocated GLFW resources.
  // ------------------------------------------------------------------
  glfwTerminate();
  return 0;
}
void draw(Shader shader, GLFWwindow* window, int texture) {
    shader.use();

    // view/projection transformations
    glm::mat4 projection =
        glm::perspective(glm::radians(camera.Zoom),
            (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

    glm::mat4 view = camera.GetViewMatrix();
    shader.setMat4("projection", projection);
    shader.setMat4("view", view);


    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glBindVertexArray(Mesh::VAO);

    tileMap.Draw();
}

// process all input: query GLFW whether relevant keys are pressed/released
// this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);

  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    camera.ProcessKeyboard(FORWARD, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    camera.ProcessKeyboard(BACKWARD, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    camera.ProcessKeyboard(LEFT, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    camera.ProcessKeyboard(RIGHT, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback
// function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  // make sure the viewport matches the new window dimensions; note that width
  // and height will be significantly larger than specified on retina
  // displays.
  glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow *window, double xposd, double yposd) {
  float xpos = static_cast<float>(xposd);
  float ypos = static_cast<float>(yposd);
  if (firstMouse) {
    lastX = xpos;
    lastY = ypos;
    firstMouse = false;
  }

  float xoffset = xpos - lastX;
  float yoffset =
      lastY - ypos; // reversed since y-coordinates go from bottom to top

  lastX = xpos;
  lastY = ypos;

  if (GLFW_CURSOR_DISABLED == glfwGetInputMode(window, GLFW_CURSOR)) {
      camera.ProcessMouseMovement(xoffset, yoffset);
  }
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
  camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

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

// utility function for loading a 2D texture from file
// ---------------------------------------------------
unsigned int loadTexture(char const *path) {
  unsigned int textureID;
  glGenTextures(1, &textureID);

  int width, height, nrComponents;
  unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
  if (data) {
    GLenum format;
    if (nrComponents == 1)
      format = GL_RED;
    else if (nrComponents == 3)
      format = GL_RGB;
    else if (nrComponents == 4)
      format = GL_RGBA;

    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
                 GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
     
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    //GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    stbi_image_free(data);
  } else {

    std::cout << "Texture failed to load at path: " << path << std::endl;
    stbi_image_free(data);
  }

  return textureID;
}

