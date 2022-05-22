#ifndef Data_h
#define Data_h
#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <sstream>
#include <map>
#include <vector>


const int settingElementsTotal = 4;
const int TILE_SIZE = 40;
const int ROWS = 20;
const int HIDDEN_ROWS = 10;
const int COLS = 10;
const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
const int SCREEN_FPS = 60;
const int SCREEN_TICK_PER_FRAME = 1000 / SCREEN_FPS;
const int initVelocity = 1000;
const int delimitedLine = -2;
const int delayBeforeDied = 3;
const int scoreMaxMem = 5;
const SDL_Color WHITE_COLOR = {255, 255, 255};
const SDL_Color BLACK_COLOR = {0, 0, 0};
const SDL_Color CYAN_COLOR = {0, 255, 255};
const SDL_Color DARK_CYAN_COLOR = {0, 190, 190};
const SDL_Color GOLD_YELLOW_COLOR = {255, 204, 53};

const std::string backGroundPicture = "assets/Pictures/cyber_background.png";
const std::string menuPicturePath = "assets/Pictures/tabs_menu.png";
const std::string gameOverBgPath = "assets/Pictures/game_over_path.png";
const std::string play_again_button = "assets/Pictures/play_again_button.png";
const std::string play_again_button_ = "assets/Pictures/play_again_button_.png";
const std::string tetroTempP = "assets/Pictures/7block.png";
const std::string back_button = "assets/Pictures/return_button.png";
const std::string back_button_ = "assets/Pictures/return_button_.png";

const std::string menuButton[] = {"assets/Pictures/menu_button0.png","assets/Pictures/menu_button1.png","assets/Pictures/menu_button2.png","assets/Pictures/menu_button3.png"};
const std::string menuButton_[] = {"assets/Pictures/menu_button0_.png","assets/Pictures/menu_button1_.png","assets/Pictures/menu_button2_.png","assets/Pictures/menu_button3_.png"};

const std::string grid_frame = "assets/Pictures/GridFrame.png";

const std::string helpsBgP = "assets/Pictures/help_credits.png";
const std::string help_help_buttonP = "assets/Pictures/help_help_button.png";
const std::string help_help_buttonP_ = "assets/Pictures/help_help_button_.png";
const std::string help_about_buttonP = "assets/Pictures/help_about_button.png";
const std::string help_about_buttonP_ = "assets/Pictures/help_about_button_.png";

const std::string help_copyright_buttonP = "assets/Pictures/helpCB.png";

const std::string help_copyright_buttonP_ = "assets/Pictures/help_copyright_button_.png";
const std::string help_help_textP = "assets/Pictures/helps_help_tex.png";

const std::string help_about_textP = "assets/Pictures/helps_about_tex.png";
const std::string help_copyright_textP = "assets/Pictures/helps_copyright_tex.png";

const std::string winnerIconP = "assets/Pictures/winner.png";
const std::string battle_endedP = "assets/Pictures/battle_ended.png";
const std::string drawTextP = "assets/Pictures/draw.png";
const std::string victoryTextP = "assets/Pictures/victory.png";
const std::string player1winP = "assets/Pictures/player1_win.png";
const std::string player2winP = "assets/Pictures/player2_win.png";
const std::string drawP = "assets/Pictures/draw.png";
const std::string tabSettingsP = "assets/Pictures/tabs_settings.png";
const std::string right_pressP = "assets/Pictures/rightPress.png";
const std::string left_pressP = "assets/Pictures/leftPress.png";
const std::string right_pressP_ = "assets/Pictures/rightPress_.png";
const std::string left_pressP_ = "assets/Pictures/leftPress_.png";
const std::string ghostBlockP = "assets/Pictures/ghostBlocks.png";
const std::string clearHighestScoreP = "assets/Pictures/clear_highest_score.png";
const std::string clearSettingsP = "assets/Pictures/clear_settings.png";
const std::string clearHighestScoreP_ = "assets/Pictures/clear_highest_score_.png";
const std::string clearSettingsP_ = "assets/Pictures/clear_settings_.png";
const std::string fontVarino1P = "fonts/VarinonormalRegular-nRYg4.otf";

const std::string ES_MouseClickP = "assets/Sounds/MouseClick.wav";
const std::string se_moveP = "assets/Sounds/se_game_move.wav";
const std::string se_holdP = "assets/Sounds/se_game_hold.wav";
const std::string se_dropP = "assets/Sounds/se_game_harddrop.wav";
const std::string se_startP = "assets/Sounds/me_game_start1.wav";
const std::string se_doubleP = "assets/Sounds/se_game_double.wav";
const std::string se_pauseP = "assets/Sounds/se_game_pause.wav";
const std::string se_rotateP = "assets/Sounds/se_game_rotate.wav";
const std::string se_countP = "assets/Sounds/se_game_count.wav";
const std::string me_gameoverP = "assets/Sounds/me_game_gameover.mp3";
const std::string se_gameoverP = "assets/Sounds/me_game_gameover.wav";
const std::string se_lineCompletedP[] = {"assets/Sounds/se_game_single.wav", "assets/Sounds/se_game_double.wav", "assets/Sounds/se_game_triple.wav", "assets/Sounds/se_game_tetris.wav"};
static Mix_Music* playingSoundtrack;
static Mix_Music* themeSoundtrack;
static Mix_Chunk* ES_MouseClick;
static Mix_Chunk* se_move;
static Mix_Chunk* se_hold;
static Mix_Chunk* se_drop;
static Mix_Chunk* se_start;
static Mix_Chunk* se_double;
static Mix_Chunk* se_pause;
static Mix_Chunk* se_rotate;
static Mix_Chunk* se_count;
static Mix_Music* me_gameover;
static Mix_Chunk* se_gameover;
static Mix_Chunk* se_lineCompleted[4];
extern TTF_Font* gFont1;
extern TTF_Font* fontVarino1;
extern TTF_Font* fontStar_40;
extern TTF_Font* fontStar_50;
extern std::vector<int> highestScore;
extern std::map<std::string, int> settingsElement;


enum Tabs {
    Menu = -1,
    InGame_SoloMode,
    InGame_BattleMode,
    Settings,
    Helps,
    ExitGame,
    allButtonsOfMenu
};

enum GameMode {
    Player1,
    SinglePlay,
    Player2
};
void playSoundEffects(Mix_Chunk* chunk, int loop = 0, int channel = -1);


#endif