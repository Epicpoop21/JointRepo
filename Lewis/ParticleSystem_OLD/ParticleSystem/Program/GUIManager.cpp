#include "GUIManager.h"

GUIManager::GUIManager() : windowFlags(0), window(nullptr), count(0)
{

}

GUIManager::~GUIManager()
{
}

void GUIManager::Setup(GLFWwindow* window, GameData* gameData) 
{
	this->window = window;
	this->gameData = gameData;

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

	ImGui_ImplGlfw_InitForOpenGL(window, 1);
	ImGui_ImplOpenGL3_Init();
}

void GUIManager::Render() 
{
	const ImGuiViewport* mainViewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(300, 500), ImGuiCond_FirstUseEver);

	if (!ImGui::Begin("Config", nullptr, windowFlags)) {
		ImGui::End();
		return;
	}

	ImGui::Text("Time elapsed: (%i)", (int)gameData->elapasedTime);
	ImGui::Spacing();
	ImGui::SeparatorText("Particle Data");

	ImGui::BeginDisabled(gameData->currentParticle == nullptr);
	if (gameData->currentParticle == nullptr) {
		glm::vec2 zeroVec2 = glm::vec2(0, 0);
		ImGui::SliderFloat2("Particle Velocity", glm::value_ptr(zeroVec2), -100, 100, "%.5f");
		ImGui::Text("Overall velocity: %d", 0.0f);
	}
	else {
		ImGui::SliderFloat2("Particle Velocity", glm::value_ptr(gameData->currentParticle->velocity), -100, 100, "%.5f");
		ImGui::Text("Overall velocity: %f", glm::length(gameData->currentParticle->velocity));
	}
	ImGui::EndDisabled();

	ImGui::Text("Kinetic energy: %f", gameData->ke);
	ImGui::Spacing();
	ImGui::SeparatorText("Simulator Config");
	ImGui::SliderFloat("Bounce", &gameData->particleBounciness, 0.0f, 2.0f);
	ImGui::SliderFloat("Repel distance", &gameData->particleRepelDistance, 0.0f, 5.0f);
	ImGui::SliderFloat("Mouse radius", &gameData->mouseRadius, 0.0f, 2000.0f);
	ImGui::SliderFloat("Repulsion/attaction", &gameData->mouseInteractStrength, -1000.0f, 1000.0f);

	ImGui::Checkbox("Collisions", &gameData->collisions);
	ImGui::Checkbox("Gravity", &gameData->gravity);

	ImGui::End();
}
