

#ifndef Definitions_h
#define Definitions_h

#define SPLASH_SCENE_BACKGROUND_FILEPATH    "res/Splash Background.png"
#define SPLASH_SCENE_SHOW_TIME              2.0

#define MAIN_MENU_SCENE_BACKGROUND_FILEPATH "res/Main Menu Background.png"
#define GAME_BACKGROUND_FILEPATH            "res/Main Menu Background.png"
#define MAIN_MENU_TITLE_FILEPATH            "res/Game Title.png"
#define MAIN_MENU_PLAY_BUTTON               "res/Play Button.png"
#define MAIN_MENU_PLAY_BUTTON_PRESSED       "res/Play Button.png"
#define SOUND_ON_BUTTON                     "res/Sound On.png"
#define SOUND_ON_BUTTON_PRESSED             "res/Sound On.png"
#define SOUND_OFF_BUTTON                    "res/Sound Off.png"
#define SOUND_OFF_BUTTON_PRESSED            "res/Sound Off.png"
#define ACHIEVEMENT_BUTTON                  "res/Achievements.png"
#define ACHIEVEMENT_BUTTON_PRESSED          "res/Achievements.png"
#define MAIN_MENU_PLAY_BUTTON_OUTER         "res/Play Button Outer.png"

#define TAG_MAIN_MENU_PLAY_BUTTON           0
#define TAG_ACHIEVEMENT_BUTTON              1

#define SCENE_TRANSITION_TIME               0.6

#define GRID_FILEPATH                       "res/Grid.png"

#define X_PIECE_FILEPATH                    "res/X.png"
#define O_PIECE_FILEPATH                    "res/O.png"
#define X_WINNING_PIECE_FILEPATH            "res/X Win.png"
#define O_WINNING_PIECE_FILEPATH            "res/O Win.png"

#define X_PIECE                             8
#define O_PIECE                             3
#define EMPTY_PIECE                         0

#define PLAYER_PIECE                        X_PIECE
#define AI_PIECE                            O_PIECE

#define STATE_PLAYING                       98
#define STATE_PAUSED                        97
#define STATE_WON                           96
#define STATE_LOSE                          95
#define STATE_PLACING_PIECE                 94
#define STATE_AI_PLAYING                    93
#define STATE_DRAW

#define PIECE_FADE_IN_TIME                  0.5

#define LOSE_REWARD                         -60
#define WIN_REWARD                          80
#define ONE_PIECE_REWARD                    2
#define TWO_PIECES_REWARD                   20
#define PREVENT_REWARD                      1

#endif /* Definitions_h */
