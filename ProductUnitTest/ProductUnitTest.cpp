#include "CppUnitTest.h"
#include "../Product/Product.cpp"
#include <stdexcept>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace ProductUnitTest
{
	TEST_CLASS(FoodUnitTest)
	{
	public:
		
		TEST_METHOD(FoodConstructor)
		{
			vector<double> nutrition{ 76.0, 0.1, 17.0, 2.2, 2.0, 0.006 };
			Food f("potato", 50, 1000, nutrition);
			Assert::IsTrue("potato" == f.get_name());
			Assert::AreEqual(50, f.get_price());
			Assert::AreEqual(1000, f.get_weight());
			Assert::AreEqual(76.0, f.get_kcal_per_100g(), 0.001);
			Assert::AreEqual(0.1, f.get_fat_per_100g(), 0.001);
			Assert::AreEqual(17.0, f.get_carbohydrates_per_100g(), 0.001);
			Assert::AreEqual(2.2, f.get_fibre_per_100g(), 0.001);
			Assert::AreEqual(2.0, f.get_protein_per_100g(), 0.001);
			Assert::AreEqual(0.006, f.get_salt_per_100g(), 0.001);
		}
	};
}
