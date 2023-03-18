import subprocess
import os
import re

if os.path.isdir('./Team22/Code22/cmake-build-debug/src'):
    start = './Team22/Code22/cmake-build-debug/src'
else:
    start = './Team22/Code22/build/src'

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
                      ("TestCombinationTwoClauses/Sample_source.txt", "TestCombinationTwoClauses/Sample_queries.txt")]

testCaseRegex = re.compile(R"(\n(\d+) - ((?:.|\n(?!\d+ - ))*))")
correctAnswerRegex = re.compile("(Correct answer: (.)*)")
actualAnswerRegex = re.compile("(Your answer: (.)*)")
missingAnswerRegex = re.compile("(Missing: (.)*)")
additionalAnswerRegex = re.compile("(Additional: (.)*)")
queryRegex = re.compile(R"(\n.*\n(.*)\n(.*))")

wrong = []
queries = []
correct = []

for source, query in source_query_pairs:
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

        if matchMissing is None and matchAdditional is None:
            correct.append(arg1)
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
                  f"\n{q[4]}")
        exit(1)
