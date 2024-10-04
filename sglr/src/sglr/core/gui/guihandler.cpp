#include "sglr/core/gui/guihandler.h"

namespace sglr
{
	void gui::init(SDL_Window* window, SDL_GLContext gl_context)
	{

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		ImGuiIO& io = ImGui::GetIO(); (void)io;
		
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.IniFilename = "guiconfig.ini";

		ImGui::StyleColorsDark();

		ImGui_ImplSDL3_InitForOpenGL(window, gl_context);
		ImGui_ImplOpenGL3_Init("#version 430");

		gui x;
		x.font = ImGui::GetIO().Fonts->AddFontFromFileTTF("fonts/Figtree-Medium.ttf", 15, NULL, ImGui::GetIO().Fonts->GetGlyphRangesDefault());
		
	}

	void gui::destroy()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplSDL3_Shutdown();
		ImGui::DestroyContext();
	}

	void gui::update()
	{
		ImGui_ImplOpenGL3_NewFrame(); 
		ImGui_ImplSDL3_NewFrame(); 
		ImGui::NewFrame(); 
	}
	
	void gui::setupStyle() // uses custom ImThemes style
	{
		ImGuiStyle& style = ImGui::GetStyle();

		style.Alpha = 1.0f;
		style.DisabledAlpha = 0.300000011920929f;
		style.WindowPadding = ImVec2(20.0f, 20.0f);
		style.WindowRounding = 12.80000019073486f;
		style.WindowBorderSize = 1.0f;
		style.WindowMinSize = ImVec2(20.0f, 20.0f);
		style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
		style.WindowMenuButtonPosition = ImGuiDir_None;
		style.ChildRounding = 6.900000095367432f;
		style.ChildBorderSize = 1.0f;
		style.PopupRounding = 0.0f;
		style.PopupBorderSize = 1.0f;
		style.FramePadding = ImVec2(20.0f, 5.0f);
		style.FrameRounding = 5.199999809265137f;
		style.FrameBorderSize = 0.0f;
		style.ItemSpacing = ImVec2(8.0f, 4.0f);
		style.ItemInnerSpacing = ImVec2(4.0f, 4.0f);
		style.CellPadding = ImVec2(4.0f, 10.0f);
		style.IndentSpacing = 10.0f;
		style.ColumnsMinSpacing = 6.0f;
		style.ScrollbarSize = 15.39999961853027f;
		style.ScrollbarRounding = 10.0f;
		style.GrabMinSize = 9.300000190734863f;
		style.GrabRounding = 20.0f;
		style.TabRounding = 0.0f;
		style.TabBorderSize = 0.0f;
		style.TabMinWidthForCloseButton = 0.0f;
		style.ColorButtonPosition = ImGuiDir_Right;
		style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
		style.SelectableTextAlign = ImVec2(0.0f, 0.0f);
		
		style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
		style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.5070357918739319f, 0.5479395389556885f, 0.615686297416687f, 1.0f);
		style.Colors[ImGuiCol_WindowBg] = ImVec4(0.003921568859368563f, 0.01568627543747425f, 0.03529411926865578f, 1.0f);
		style.Colors[ImGuiCol_ChildBg] = ImVec4(0.01691656932234764f, 0.04007508233189583f, 0.0784313753247261f, 0.5f);
		style.Colors[ImGuiCol_PopupBg] = ImVec4(0.04036908596754074f, 0.06208018958568573f, 0.09803921729326248f, 1.0f);
		style.Colors[ImGuiCol_Border] = ImVec4(0.01568627543747425f, 0.04313725605607033f, 0.0784313753247261f, 1.0f);
		style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.01568627543747425f, 0.04313725605607033f, 0.0784313753247261f, 1.0f);
		style.Colors[ImGuiCol_FrameBg] = ImVec4(0.01845443993806839f, 0.05813147127628326f, 0.1176470592617989f, 1.0f);
		style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.02768165990710258f, 0.08369631320238113f, 0.1764705926179886f, 1.0f);
		style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.03075739927589893f, 0.09299590438604355f, 0.196078434586525f, 1.0f);
		style.Colors[ImGuiCol_TitleBg] = ImVec4(0.004306036047637463f, 0.01744849048554897f, 0.03921568766236305f, 1.0f);
		style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.003921568859368563f, 0.01568627543747425f, 0.03921568766236305f, 1.0f);
		style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.009611687622964382f, 0.03874075412750244f, 0.09803921729326248f, 1.0f);
		
		style.Colors[ImGuiCol_TabSelectedOverline] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
		style.Colors[ImGuiCol_TabDimmedSelectedOverline] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);

		style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.03229527175426483f, 0.04749304801225662f, 0.0784313753247261f, 1.0f);
		style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.0313725471496582f, 0.07861591875553131f, 0.1568627506494522f, 1.0f);
		style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.1049596294760704f, 0.1997937262058258f, 0.3568627536296844f, 1.0f);
		style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.1168781220912933f, 0.2205124646425247f, 0.3921568691730499f, 1.0f);
		style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.1285659223794937f, 0.2425637096166611f, 0.4313725531101227f, 1.0f);
		style.Colors[ImGuiCol_CheckMark] = ImVec4(0.4192233681678772f, 0.4754696190357208f, 0.5686274766921997f, 1.0f);
		style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.1768550425767899f, 0.2579098641872406f, 0.3921568691730499f, 1.0f);
		style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.2652825713157654f, 0.3868648111820221f, 0.5882353186607361f, 1.0f);
		style.Colors[ImGuiCol_Button] = ImVec4(0.03014225326478481f, 0.1221394389867783f, 0.2745098173618317f, 1.0f);
		style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.03567858412861824f, 0.1403550654649734f, 0.3137255012989044f, 1.0f);
		style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.04013840854167938f, 0.1578994393348694f, 0.3529411852359772f, 1.0f);
		style.Colors[ImGuiCol_Header] = ImVec4(0.0156862735748291f, 0.04226066544651985f, 0.0784313753247261f, 1.0f);
		style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.02352941036224365f, 0.06339100003242493f, 0.1176470592617989f, 1.0f);
		style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.0313725471496582f, 0.0845213308930397f, 0.1568627506494522f, 1.0f);
		style.Colors[ImGuiCol_Separator] = ImVec4(0.004306036047637463f, 0.01744849048554897f, 0.03921568766236305f, 1.0f);
		style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.02153017930686474f, 0.08724245429039001f, 0.196078434586525f, 1.0f);
		style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.03014225326478481f, 0.1221394389867783f, 0.2745098173618317f, 1.0f);
		style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.161476343870163f, 0.2483207583427429f, 0.3921568691730499f, 0.4274509847164154f);
		style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.161476343870163f, 0.2483207583427429f, 0.3921568691730499f, 0.6549019813537598f);
		style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.161476343870163f, 0.2483207583427429f, 0.3921568691730499f, 1.0f);
		
		style.Colors[ImGuiCol_Tab] = ImVec4(0.01568627543747425f, 0.04313725605607033f, 0.0784313753247261f, 0.5f);
		style.Colors[ImGuiCol_TabHovered] = ImVec4(0.0235294122248888f, 0.062745101749897f, 0.1176470592617989f, 0.5f);
		style.Colors[ImGuiCol_TabActive] = ImVec4(0.0313725508749485f, 0.08627451211214066f, 0.1568627506494522f, 0.5f);
		style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.01568627543747425f, 0.07058823853731155f, 0.1568627506494522f, 0.5f);
		style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.01568627543747425f, 0.07058823853731155f, 0.1568627506494522f, 0.5);
		
		style.Colors[ImGuiCol_PlotLines] = ImVec4(0.06028450652956963f, 0.2442788779735565f, 0.5490196347236633f, 1.0f);
		style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.4392156600952148f, 0.6503344774246216f, 1.0f, 1.0f);
		style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.04306035861372948f, 0.17448490858078f, 0.3921568691730499f, 1.0f);
		style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.06459054350852966f, 0.26172736287117f, 0.5882353186607361f, 1.0f);
		style.Colors[ImGuiCol_TableHeaderBg] = ImVec4(0.004306036047637463f, 0.01744849048554897f, 0.03921568766236305f, 1.0f);
		style.Colors[ImGuiCol_TableBorderStrong] = ImVec4(0.02153017930686474f, 0.08724245429039001f, 0.196078434586525f, 1.0f);
		style.Colors[ImGuiCol_TableBorderLight] = ImVec4(0.02153017930686474f, 0.05027927830815315f, 0.196078434586525f, 1.0f);
		style.Colors[ImGuiCol_TableRowBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
		style.Colors[ImGuiCol_TableRowBgAlt] = ImVec4(0.2980392277240753f, 0.2980392277240753f, 0.2980392277240753f, 0.09000000357627869f);
		style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.1072202920913696f, 0.4344674348831177f, 0.9764705896377563f, 0.3490196168422699f);
		style.Colors[ImGuiCol_DragDropTarget] = ImVec4(0.06459054350852966f, 0.26172736287117f, 0.5882353186607361f, 1.0f);
		style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.01568627543747425f, 0.07058823853731155f, 0.1568627506494522f, 0.0f);
		style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(0.01568627543747425f, 0.07058823853731155f, 0.1568627506494522f, 0.0f);
		style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.2000000029802322f, 0.2000000029802322f, 0.2000000029802322f, 0.0f);
		style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.2000000029802322f, 0.2000000029802322f, 0.2000000029802322f, 0.0f);
	}

	void gui::makeDockSpace()
	{
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;

		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

		const ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->WorkPos);
		ImGui::SetNextWindowSize(viewport->WorkSize);
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("sglrdockspace", nullptr, window_flags);
		ImGui::PopStyleVar();
		ImGui::PopStyleVar(2);

		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("sglrdocking");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		ImGui::BeginMenuBar();

		gui x;
		ImGui::PushFont(x.font);
		ImGui::TextDisabled("SGLR");
		ImGui::PopFont();
		ImGui::EndMenuBar();
		ImGui::End();
	}

	void gui::render()
	{
		ImGui::Render(); 
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData()); 
	}

}
