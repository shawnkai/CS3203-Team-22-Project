import subprocess
import os
import re

if os.path.isdir('./Team22/Code22/cmake-build-debug/src'):
    start = './Team22/Code22/cmake-build-debug/src'
elif os.path.isdir('./Team22/Code22/build/src'):
    start = './Team22/Code22/build/src'
else:
    start = './Team22/Code22/out/build/x64-Debug/src'

# Unit Testing
print("Running Unit Tests...")
result = subprocess.run([start + '/unit_testing/unit_testing'], stdout=subprocess.PIPE)

result = result.stdout.decode()

if "All tests passed" not in result:
    print(result)
    exit(1)

print("Unit Tests Passed")

# Integration Testing
print("Running Integration Tests...")
result = subprocess.run([start + '/integration_testing/integration_testing'], stdout=subprocess.PIPE)

result = result.stdout.decode()

if "All tests passed" not in result:
    exit(1)

print("Integration Tests Passed")

# System Testing
print("Running System Tests...")
source_query_pairs = [("TestBasicQueriesInitialSubmissionForMilestone1/Sample_source2.txt",
                       "TestBasicQueriesInitialSubmissionForMilestone1/Sample_queries2.txt"),
                      ("TestAssignmentPatternClause/TestAssignmentPatternSourceProgram.txt",
                       "TestAssignmentPatternClause/TestAssignmentPatternQueries.txt"),
                      ("TestBasicQueriesInitialSubmissionForMilestone1/Sample_source3.txt",
                       "TestBasicQueriesInitialSubmissionForMilestone1/Sample_queries3.txt"),
                      ("TestFollowsAndParentRelationship/Sample_source_follows.txt",
                       "TestFollowsAndParentRelationship/Sample_queries_follows.txt"),
                      ("TestModifiesAndUsesRelationship/Modifies_Simplified_Testing_source.txt",
                       "TestModifiesAndUsesRelationship/Modifies_Simplified_Testing_queries.txt"),
                      ("TestModifiesAndUsesRelationship/Uses_Simplified_Testing_source.txt",
                       "TestModifiesAndUsesRelationship/Uses_Simplified_Testing_queries.txt"),
                      ("TestCombinationTwoClauses/Sample_source.txt", "TestCombinationTwoClauses/Sample_queries.txt"),
                      ("TestMultipleExpressions/Multiple_Expressions_Source.txt", "TestMultipleExpressions"
                                                                                  "/Multiple_Expressions_Queries.txt"),
                      ("Ms2Testing/Milestone_2_Testing_Source.txt", "Ms2Testing/Milestone_2_Testing_Queries.txt"),
                      ("TestWithClause/Sample_source_with.txt", "TestWithClause/Sample_queries_with.txt"),
                      ("TestWithClause/TestWithClauseSource.txt", "TestWithClause/TestWithClauseQueries.txt"),
                      ("TestWithClause/TestWithClauseSource2.txt", "TestWithClause/TestWithClauseQueries2.txt"),
                      ("TestIfWhileAssignPattern/Sample_source.txt", "TestIfWhileAssignPattern/Sample_queries.txt"),
                      ("TestAndKeyword/Sample_source.txt", "TestAndKeyword/Sample_queries.txt"),
                      ("TestIfWhileAssignPattern/Sample_source.txt", "TestIfWhileAssignPattern/Sample_queries.txt"),
                      ("TestAndKeyword/Sample_source.txt", "TestAndKeyword/Sample_queries.txt"),
                      ("TestIfPatternClause/TestIfAndWhilePatternClauseSourceProgram.txt", "TestIfPatternClause/TestIfPatternClauseQueries.txt"),
                      ("TestWhilePatternClause/TestIfAndWhilePatternClauseSourceProgram.txt", "TestWhilePatternClause/TestWhilePatternClauseQueries.txt"),
                      ("TestCallsExpression/Sample_source.txt", "TestCallsExpression/Sample_queries.txt"),
                      ("TestCallsExpression/Calls_Testing_Source.txt", "TestCallsExpression/Calls_Testing_Queries.txt"),
                      ("TestBoolean/Simple_Test_Source.txt", "TestBoolean/Simple_Test_Queries.txt"),
                      ("TestDemo2Features/Sample_source.txt", "/TestDemo2Features/Sample_queries.txt")]

testCaseRegex = re.compile(R"(\n(\d+)\s*-\s*.*\n((?:.|\n(?!\d+\s*-\s*))*))")
correctAnswerRegex = re.compile("(Correct answer: (.)*)")
actualAnswerRegex = re.compile("(Your answer: (.)*)")
missingAnswerRegex = re.compile("(Missing: (.)*)")
additionalAnswerRegex = re.compile("(Additional: (.)*)")
queryRegex = re.compile(R"(\n.*\n(.*)\n(.*))")

for source, query in source_query_pairs:
    wrong = []
    queries = []
    correct = []
    command = [start + "/autotester/autotester", "./Team22/Tests22/" + source, "./Team22/Tests22/" + query,
               "./Team22/Tests22/Sample_out.xml"]

    result = subprocess.run(command, stdout=subprocess.PIPE)
    result = result.stdout.decode()

    for case in re.finditer(testCaseRegex, result):
        arg1 = case.group(2)
        arg2 = case.group(1)

        matchCorrect = re.search(correctAnswerRegex, arg2)

        matchActual = re.search(actualAnswerRegex, arg2)

        matchAdditional = re.search(additionalAnswerRegex, arg2)

        matchMissing = re.search(missingAnswerRegex, arg2)

        matchQuery = re.search(queryRegex, arg2)

        if matchMissing is None and matchAdditional is None and "<exception/>" not in arg2:
            correct.append(arg1)
        elif "<exception/>" in arg2:
            wrong.append(arg1)
            queries.append(
                [matchQuery.group(2) + "\n" + matchQuery.group(3), "Throws Exception", "Throws Exception", "Throws Exception", "Throws Exception"])
        else:
            missing = matchMissing.group(0)

            additional = matchAdditional.group(0)

            wrong.append(arg1)
            queries.append(
                [matchQuery.group(2) + "\n" + matchQuery.group(3), matchCorrect.group(0), matchActual.group(0),
                 matchMissing.group(0), matchAdditional.group(0)])

    print(f"Test Stats for {source}:"
          f"\nCorrect Evaluations: {len(correct)}"
          f"\nIncorrect Evaluations: {len(wrong)}\n")

    if len(queries) != 0:
        print("Incorrect Tests:")
        for q in queries:
            print(f"Query: {q[0]}"
                  f"\n{q[1]}"
                  f"\n{q[2]}"
                  f"\n{q[3]}"
                  f"\n{q[4]}\n")
        exit(1)
