add_subdirectory(Core)
add_subdirectory(Plugins)

if (DSPTOOL)
	add_subdirectory(DSPTool)
endif()

if (UNITTESTS)
	add_subdirectory(UnitTests)
endif()

# TODO: Add DSPSpy and TestSuite. Preferrably make them option()s and cpack components
