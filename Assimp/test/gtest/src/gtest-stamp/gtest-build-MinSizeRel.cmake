

set(command "D:/_dev/cmake/bin/cmake.exe;--build;.;--config;MinSizeRel")
execute_process(
  COMMAND ${command}
  RESULT_VARIABLE result
  OUTPUT_FILE "D:/UWS/08_Real_TIme_3d/code/QSO/Assimp/test/gtest/src/gtest-stamp/gtest-build-out.log"
  ERROR_FILE "D:/UWS/08_Real_TIme_3d/code/QSO/Assimp/test/gtest/src/gtest-stamp/gtest-build-err.log"
  )
if(result)
  set(msg "Command failed: ${result}\n")
  foreach(arg IN LISTS command)
    set(msg "${msg} '${arg}'")
  endforeach()
  set(msg "${msg}\nSee also\n  D:/UWS/08_Real_TIme_3d/code/QSO/Assimp/test/gtest/src/gtest-stamp/gtest-build-*.log")
  message(FATAL_ERROR "${msg}")
else()
  set(msg "gtest build command succeeded.  See also D:/UWS/08_Real_TIme_3d/code/QSO/Assimp/test/gtest/src/gtest-stamp/gtest-build-*.log")
  message(STATUS "${msg}")
endif()
