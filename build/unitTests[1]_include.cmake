if(EXISTS "/home/martin/calculator/build/unitTests[1]_tests.cmake")
  include("/home/martin/calculator/build/unitTests[1]_tests.cmake")
else()
  add_test(unitTests_NOT_BUILT unitTests_NOT_BUILT)
endif()
