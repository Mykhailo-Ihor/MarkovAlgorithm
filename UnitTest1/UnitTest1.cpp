#include "pch.h"
#include "CppUnitTest.h"
#include "../Project6/Source.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MarkovAlgorithmTests
{
	TEST_CLASS(StringTests)
	{
	public:
		TEST_METHOD(TestSubstitute)
		{
			String str("abacada");
			str.substitute("a", "z");
			Assert::AreEqual(std::string("zbzczdz"), str.toString());
		}

		TEST_METHOD(TestApplySubstitutions)
		{
			String str("abacada");
			std::vector<std::pair<std::string, std::string>> subs = { {"a", "z"}, {"b", ""} };
			while(str.applySubstitutions(subs));
			Assert::AreEqual(std::string("zzczdz"), str.toString());
		}

		TEST_METHOD(TestEmptySubstitution)
		{
			String str("abcd");
			std::vector<std::pair<std::string, std::string>> subs = { {"e", ""} };
			str.applySubstitutions(subs);
			Assert::AreEqual(std::string("abcd"), str.toString());
		}

		TEST_METHOD(TestSubstituteWithEmptyString)
		{
			String str("abacada");
			str.substitute("a", "");
			Assert::AreEqual(std::string("bcd"), str.toString());
		}

		TEST_METHOD(TestApplySubstitutionsNoChange)
		{
			String str("abacada");
			std::vector<std::pair<std::string, std::string>> subs = { {"x", "y"} };
			str.applySubstitutions(subs);
			Assert::AreEqual(std::string("abacada"), str.toString());
		}
	};
}