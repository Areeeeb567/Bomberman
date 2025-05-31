project(Project_lib)

set(SOURCE_FILES
        Game.cpp
        Game.h
        GameEvent.cpp
        GameEvent.h
        Menu.cpp
        Menu.h
        Gameplay.cpp
        Gameplay.h
        GameGrid.cpp
        GameGrid.h
        Player.cpp
        Player.h
        Bomb.cpp
        Bomb.h
        Entity.cpp
        Entity.h
        Enemy.cpp
        Enemy.h
        Ballom.h
        Onil.h
        Button.h
)

add_library(Project_lib STATIC ${SOURCE_FILES})
