all:
	g++ main.cpp Engine.cpp IOManager.cpp SettingsManager.cpp Setting.cpp WindowSystem.cpp RenderSystem.cpp MovementSystem.cpp ColorComponent.cpp PositionComponent.cpp DimensionsComponent.cpp VectorComponent.cpp TimekeeperSystem.cpp DeltaMessage.cpp Entity.cpp libSOIL.a -lGLEW -lglfw -lGL -lGLU -lgdiplus -o rts

