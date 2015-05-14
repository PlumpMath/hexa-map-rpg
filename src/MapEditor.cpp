//#include "MapEditor.h"
//
//MapEditor::MapEditor()
//{
//}
//MapEditor::~MapEditor()
//{
//}
//
//void Run() {
//    bool quit = false;
//    bool refresh = true;
//    SDL_Event event;
//
//    Stage stage;
//    Graphic grp;
//
//    while(!(quit)) {
//        while(SDL_PollEvent(&event)) {
//            // 종료 이벤트
//            if (event.type == SDL_QUIT) {
//                quit = true;
//            }
//            // 키보드 입력
//            if ( event.type == SDL_KEYDOWN ) {
//                switch( event.key.keysym.sym ) {
//                    case SDLK_ESCAPE:
//                        quit = true;
//                        break;
//
//                    case SDLK_F1 :
//                        //stage.SightToggle();
//                        stage.Update();
//                        stage.DrawMap();
//                        grp.DrawUNICODE(30, 30, 400, color_white, L"<blue>격자<black>를 %d번으로 변경합니다.", grp.GetGrid());
//                        grp.Refresh();
//                        break;
//
//                    case SDLK_F2 :
//                        grp.ChangeGrid();
//                        stage.Update();
//                        stage.DrawMap();
//                        grp.DrawUNICODE(30, 30, 400, color_white, L"<blue>격자<black>를 %d번으로 변경합니다.", grp.GetGrid());
//                        grp.Refresh();
//                        break;
//
//                    case SDLK_2 :
//                        stage.RandomizeTerrain();
//                        stage.Update();
//                        stage.DrawMap();
//                        grp.DrawUNICODE(30, 30, 400, color_white, L"<blue>지형<black>을 다시 생성합니다.");
//                        grp.Refresh();
//                        break;
//
//                    case SDLK_3 :
//                        stage.RandomizeWall();
//                        stage.Update();
//                        stage.DrawMap();
//                        grp.DrawUNICODE(30, 30, 400, color_white, L"<blue>벽<black>을 다시 생성합니다.");
//                        grp.Refresh();
//                        break;
//
//                    case SDLK_4 :
//                        c = 0;
//                        for (int i = 0; i < 10; i++)
//                            !(stage.CreateObject(OBJECT_NPC, TileRef(TILESET_CHARACTER0, Random()%25), Coord(Random()%stage.GetMapCols(), Random()%stage.GetMapRows()))) ? : c++;
//                        stage.Update();
//                        stage.DrawMap();
//                        grp.DrawUNICODE(30, 30, 400, color_white, L"<blue>NPC<black>를 추가 생성합니다. %d 개 생성, 총 %d 개.", c, stage.GetObjectCount());
//                        grp.Refresh();
//                        break;
//
//                    case SDLK_5 :
//                        stage.PrintMap("map.txt");
//                        grp.DrawUNICODE(30, 30, 400, color_white, L"맵을 파일로 출력했습니다. \"map.txt\"");
//                        grp.Refresh();
//                        break;
//
//                    case SDLK_6 :
//                        stage.DrawWallRectangleA(stage.GetObjectPos(0), 8, 8, WALL_WALL, TileRef(TILESET_WALL0, 0x1f));
//                        stage.Update();
//                        stage.DrawMap();
//                        grp.DrawUNICODE(30, 30, 400, color_white, L"사각형 벽을 만듭니다 : Type A");
//                        grp.Refresh();
//                        break;
//
//                    case SDLK_7 :
//                        stage.DrawWallRectangleB(stage.GetObjectPos(0), 8, 8, WALL_WALL, TileRef(TILESET_WALL0, 0x1f));
//                        stage.Update();
//                        stage.DrawMap();
//                        grp.DrawUNICODE(30, 30, 400, color_white, L"사각형 벽을 만듭니다 : Type B");
//                        grp.Refresh();
//                        break;
//
//                    case SDLK_8 :
//                        stage.DrawWallRectangleC(stage.GetObjectPos(0), 8, 8, WALL_WALL, TileRef(TILESET_WALL0, 0x1f));
//                        stage.Update();
//                        stage.DrawMap();
//                        grp.DrawUNICODE(30, 30, 400, color_white, L"사각형 벽을 만듭니다 : Type C");
//                        grp.Refresh();
//                        break;
//
//                    case SDLK_9 :
//                        stage.DrawMap();
//                        grp.DrawUNICODE(30, 30, 400, color_white, L"UTF-8 문자열 : %s", ws.c_str());
//                        grp.Refresh();
//                        break;
//
//                    case SDLK_KP_PLUS :
//                        if (stage.IncObjectSightRange(0)) {
//                        stage.Update();
//                        stage.DrawMap();
//                            grp.DrawUNICODE(30, 30, 400, color_white, L"시야를 늘렸습니다. 현재 시야 : %d", stage.GetObjectSightRange(0));
//                        }
//                        else {
//                            stage.Update();
//                            stage.DrawMap();
//                            grp.DrawUNICODE(30, 30, 400, color_white, L"시야를 더 늘릴 수 없습니다.");
//                        }
//                        grp.Refresh();
//                        break;
//
//                    case SDLK_KP_MINUS :
//                        if (stage.DecObjectSightRange(0)) {
//                            stage.Update();
//                            stage.DrawMap();
//                            grp.DrawUNICODE(30, 30, 400, color_white, L"시야를 줄였습니다. 현재 시야 : %d", stage.GetObjectSightRange(0));
//                        }
//                        else {
//                            stage.Update();
//                            stage.DrawMap();
//                            grp.DrawUNICODE(30, 30, 400, color_white, L"시야를 더 줄일 수 없습니다.");
//                        }
//                        grp.Refresh();
//                        break;
//
//                    default:
//                        break;
//                }
//            }
//        }
//}
