#include "pch.h"
#include "CppUnitTest.h"
#include <ctime>
#include <string>
#include "../Multiplication/Multiplication.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(UnitTest)
	{
	public:

		bool matrixEqual(double e, int m, int n, int k, int l, double* A, double* B)
			// m*n matrix A, k*l matrix B
		{
			if ((m != k) || (k != l))
				return false;
			double maxDiff = abs(A[0] - B[0]);
			double currentDiff = 0;
			for (int i=0; i < m*n; i++)
			{
				currentDiff = abs(A[i] - B[i]);
				if (currentDiff > maxDiff)
				{
					maxDiff = currentDiff;
				}
			}

			if (maxDiff <= e)
				return true;

			return false;
		}

		double* ramdomMatrix(int m, int n)
		{
			double* A = new double[m * n];
			for (int i = 0; i < m * n; i++)
			{
				A[i] = (double)(rand()) / RAND_MAX * 1000;
			}
			
			return A;
		}
		TEST_METHOD(SquareMatricesTest)
		{
			double A[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
			double expected[9] = { 30, 36, 42, 66, 81, 96, 102, 126, 150 };
			double actual[9];

			production(3, 3, 3, A, A, actual);

			bool r = matrixEqual(0.1, 3, 3, 3, 3, expected, actual);

			Assert::IsTrue(r);
		}

		TEST_METHOD(RectangularMatricesTest)
		{
			double A[12] = { -1, 2, 5, 3, 4, 6, -8, 2, 12, 1, 2, 3 };
			double B[6] = { -2, 2, 5, 7, -1, 4 };

			double expected[8] = { 7, 32, 8, 58, 14, 46, 5,	28 };
			double actual[8];

			production(4, 3, 2, A, B, actual);

			bool r = matrixEqual(0.1, 3, 3, 3, 3, expected, actual);

			Assert::IsTrue(r);
		}

		TEST_METHOD(ZeroStringSizeMatrixFirstArgument)
		{
			auto func = [] { production(0, 1, 1, new double[1]{1}, new double[1]{ 1 }, new double[1]); };

			Assert::ExpectException<std::invalid_argument>(func);
		}

		TEST_METHOD(ZeroStringSizeMatrixSecondArgument)
		{
			auto func = [] { production(1, 0, 1, new double[1]{ 1 }, new double[1]{ 1 }, new double[1]); };

			Assert::ExpectException<std::invalid_argument>(func);
		}

		TEST_METHOD(ZeroStringSizeMatrixThirdArgument)
		{
			auto func = [] { production(1, 1, 0, new double[1]{ 1 }, new double[1]{ 1 }, new double[1]); };

			Assert::ExpectException<std::invalid_argument>(func);
		}

		TEST_METHOD(EmptyMatrixFirst)
		{
			auto func = [] { production(1, 1, 1, NULL, new double[1]{ 1 }, new double[1]); };

			Assert::ExpectException<std::invalid_argument>(func);
		}

		TEST_METHOD(EmptyMatrixSecond)
		{
			auto func = [] { production(1, 1, 1, new double[1]{ 1 }, NULL, new double[1]); };

			Assert::ExpectException<std::invalid_argument>(func);
		}

		TEST_METHOD(PerformanceTest)
		{
			int workTime = 0;
			int workTimeAll = 0;
			int attempCount = 10;
			int matrixSize = 500;
			int expectedTime = 700;

			for (int i = 0; i < attempCount; i++)
			{
				double* B = ramdomMatrix(matrixSize, matrixSize);

				double *result = new double[matrixSize*matrixSize];

				int start = clock();
				production(matrixSize, matrixSize, matrixSize, B, B, result);
				int finish = clock();

				workTimeAll = workTimeAll + (finish - start);
			}
			
			workTime = workTimeAll / attempCount;
			
			std::string str = "Working time is " + std::to_string(workTime) + " tacts";
			Logger::WriteMessage(str.c_str());

			Assert::IsTrue(workTime < expectedTime);
		}
	};
}
