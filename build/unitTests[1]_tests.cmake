add_test( SharedMemmory.ReadsCorrect /home/martin/calculator/build/unitTests [==[--gtest_filter=SharedMemmory.ReadsCorrect]==] --gtest_also_run_disabled_tests)
set_tests_properties( SharedMemmory.ReadsCorrect PROPERTIES WORKING_DIRECTORY /home/martin/calculator/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test( SharedMemmory.WritesCorrect /home/martin/calculator/build/unitTests [==[--gtest_filter=SharedMemmory.WritesCorrect]==] --gtest_also_run_disabled_tests)
set_tests_properties( SharedMemmory.WritesCorrect PROPERTIES WORKING_DIRECTORY /home/martin/calculator/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test( SharedMemmory.CreatesWithRightExecutor /home/martin/calculator/build/unitTests [==[--gtest_filter=SharedMemmory.CreatesWithRightExecutor]==] --gtest_also_run_disabled_tests)
set_tests_properties( SharedMemmory.CreatesWithRightExecutor PROPERTIES WORKING_DIRECTORY /home/martin/calculator/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test( SharedMemmory.WritesUnreadMessage /home/martin/calculator/build/unitTests [==[--gtest_filter=SharedMemmory.WritesUnreadMessage]==] --gtest_also_run_disabled_tests)
set_tests_properties( SharedMemmory.WritesUnreadMessage PROPERTIES WORKING_DIRECTORY /home/martin/calculator/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test( SharedMemmory.ReadMessageReadsMessage /home/martin/calculator/build/unitTests [==[--gtest_filter=SharedMemmory.ReadMessageReadsMessage]==] --gtest_also_run_disabled_tests)
set_tests_properties( SharedMemmory.ReadMessageReadsMessage PROPERTIES WORKING_DIRECTORY /home/martin/calculator/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test( SharedMemmory.GetsUniqueIds /home/martin/calculator/build/unitTests [==[--gtest_filter=SharedMemmory.GetsUniqueIds]==] --gtest_also_run_disabled_tests)
set_tests_properties( SharedMemmory.GetsUniqueIds PROPERTIES WORKING_DIRECTORY /home/martin/calculator/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test( ServerMessage.EqualsOperatorWorksPropperly /home/martin/calculator/build/unitTests [==[--gtest_filter=ServerMessage.EqualsOperatorWorksPropperly]==] --gtest_also_run_disabled_tests)
set_tests_properties( ServerMessage.EqualsOperatorWorksPropperly PROPERTIES WORKING_DIRECTORY /home/martin/calculator/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test( ServerMessage.NotEqualOperatorWorksPropperly /home/martin/calculator/build/unitTests [==[--gtest_filter=ServerMessage.NotEqualOperatorWorksPropperly]==] --gtest_also_run_disabled_tests)
set_tests_properties( ServerMessage.NotEqualOperatorWorksPropperly PROPERTIES WORKING_DIRECTORY /home/martin/calculator/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test( Writer.WritesMessage /home/martin/calculator/build/unitTests [==[--gtest_filter=Writer.WritesMessage]==] --gtest_also_run_disabled_tests)
set_tests_properties( Writer.WritesMessage PROPERTIES WORKING_DIRECTORY /home/martin/calculator/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test( Writer.WritesOnlyIfMessageIsRead /home/martin/calculator/build/unitTests [==[--gtest_filter=Writer.WritesOnlyIfMessageIsRead]==] --gtest_also_run_disabled_tests)
set_tests_properties( Writer.WritesOnlyIfMessageIsRead PROPERTIES WORKING_DIRECTORY /home/martin/calculator/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test( Detector.detectsMessage /home/martin/calculator/build/unitTests [==[--gtest_filter=Detector.detectsMessage]==] --gtest_also_run_disabled_tests)
set_tests_properties( Detector.detectsMessage PROPERTIES WORKING_DIRECTORY /home/martin/calculator/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test( Detector.detectsMessageForTarget /home/martin/calculator/build/unitTests [==[--gtest_filter=Detector.detectsMessageForTarget]==] --gtest_also_run_disabled_tests)
set_tests_properties( Detector.detectsMessageForTarget PROPERTIES WORKING_DIRECTORY /home/martin/calculator/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test( Detector.ServerTimesOutUnreadMessages /home/martin/calculator/build/unitTests [==[--gtest_filter=Detector.ServerTimesOutUnreadMessages]==] --gtest_also_run_disabled_tests)
set_tests_properties( Detector.ServerTimesOutUnreadMessages PROPERTIES WORKING_DIRECTORY /home/martin/calculator/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test( Detector.ClientDoesNotTimeOutMessage /home/martin/calculator/build/unitTests [==[--gtest_filter=Detector.ClientDoesNotTimeOutMessage]==] --gtest_also_run_disabled_tests)
set_tests_properties( Detector.ClientDoesNotTimeOutMessage PROPERTIES WORKING_DIRECTORY /home/martin/calculator/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test( ClientServerCommunicator.AddsMessageToQueue /home/martin/calculator/build/unitTests [==[--gtest_filter=ClientServerCommunicator.AddsMessageToQueue]==] --gtest_also_run_disabled_tests)
set_tests_properties( ClientServerCommunicator.AddsMessageToQueue PROPERTIES WORKING_DIRECTORY /home/martin/calculator/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test( ClientServerCommunicator.MessagesGetUniqueIds /home/martin/calculator/build/unitTests [==[--gtest_filter=ClientServerCommunicator.MessagesGetUniqueIds]==] --gtest_also_run_disabled_tests)
set_tests_properties( ClientServerCommunicator.MessagesGetUniqueIds PROPERTIES WORKING_DIRECTORY /home/martin/calculator/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test( ClientServerCommunicator.AddsMessageIdToVector /home/martin/calculator/build/unitTests [==[--gtest_filter=ClientServerCommunicator.AddsMessageIdToVector]==] --gtest_also_run_disabled_tests)
set_tests_properties( ClientServerCommunicator.AddsMessageIdToVector PROPERTIES WORKING_DIRECTORY /home/martin/calculator/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test( ClientServerCommunicator.IdContainedWorksIfIdIsContained /home/martin/calculator/build/unitTests [==[--gtest_filter=ClientServerCommunicator.IdContainedWorksIfIdIsContained]==] --gtest_also_run_disabled_tests)
set_tests_properties( ClientServerCommunicator.IdContainedWorksIfIdIsContained PROPERTIES WORKING_DIRECTORY /home/martin/calculator/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test( ClientServerCommunicator.IdContainedWorksIfIdIsNotContained /home/martin/calculator/build/unitTests [==[--gtest_filter=ClientServerCommunicator.IdContainedWorksIfIdIsNotContained]==] --gtest_also_run_disabled_tests)
set_tests_properties( ClientServerCommunicator.IdContainedWorksIfIdIsNotContained PROPERTIES WORKING_DIRECTORY /home/martin/calculator/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test( ServerCommunicator.AddsMessageToQueue /home/martin/calculator/build/unitTests [==[--gtest_filter=ServerCommunicator.AddsMessageToQueue]==] --gtest_also_run_disabled_tests)
set_tests_properties( ServerCommunicator.AddsMessageToQueue PROPERTIES WORKING_DIRECTORY /home/martin/calculator/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test( ServerCommunicator.ProccesInputWorks /home/martin/calculator/build/unitTests [==[--gtest_filter=ServerCommunicator.ProccesInputWorks]==] --gtest_also_run_disabled_tests)
set_tests_properties( ServerCommunicator.ProccesInputWorks PROPERTIES WORKING_DIRECTORY /home/martin/calculator/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test( ServerCommunicator.FirstThreadWorks /home/martin/calculator/build/unitTests [==[--gtest_filter=ServerCommunicator.FirstThreadWorks]==] --gtest_also_run_disabled_tests)
set_tests_properties( ServerCommunicator.FirstThreadWorks PROPERTIES WORKING_DIRECTORY /home/martin/calculator/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test( ServerCommunicator.SecondThreadWorks /home/martin/calculator/build/unitTests [==[--gtest_filter=ServerCommunicator.SecondThreadWorks]==] --gtest_also_run_disabled_tests)
set_tests_properties( ServerCommunicator.SecondThreadWorks PROPERTIES WORKING_DIRECTORY /home/martin/calculator/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test( ServerCommunicator.ThirdThreadWorks /home/martin/calculator/build/unitTests [==[--gtest_filter=ServerCommunicator.ThirdThreadWorks]==] --gtest_also_run_disabled_tests)
set_tests_properties( ServerCommunicator.ThirdThreadWorks PROPERTIES WORKING_DIRECTORY /home/martin/calculator/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set( unitTests_TESTS SharedMemmory.ReadsCorrect SharedMemmory.WritesCorrect SharedMemmory.CreatesWithRightExecutor SharedMemmory.WritesUnreadMessage SharedMemmory.ReadMessageReadsMessage SharedMemmory.GetsUniqueIds ServerMessage.EqualsOperatorWorksPropperly ServerMessage.NotEqualOperatorWorksPropperly Writer.WritesMessage Writer.WritesOnlyIfMessageIsRead Detector.detectsMessage Detector.detectsMessageForTarget Detector.ServerTimesOutUnreadMessages Detector.ClientDoesNotTimeOutMessage ClientServerCommunicator.AddsMessageToQueue ClientServerCommunicator.MessagesGetUniqueIds ClientServerCommunicator.AddsMessageIdToVector ClientServerCommunicator.IdContainedWorksIfIdIsContained ClientServerCommunicator.IdContainedWorksIfIdIsNotContained ServerCommunicator.AddsMessageToQueue ServerCommunicator.ProccesInputWorks ServerCommunicator.FirstThreadWorks ServerCommunicator.SecondThreadWorks ServerCommunicator.ThirdThreadWorks)
