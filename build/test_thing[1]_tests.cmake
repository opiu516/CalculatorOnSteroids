add_test( HelloTest.BasicAssertions /home/martin/calculator/build/test_thing [==[--gtest_filter=HelloTest.BasicAssertions]==] --gtest_also_run_disabled_tests)
set_tests_properties( HelloTest.BasicAssertions PROPERTIES WORKING_DIRECTORY /home/martin/calculator/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set( test_thing_TESTS HelloTest.BasicAssertions)
