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
		
		TEST_METHOD(Constructor)
		{
			array<double, 6> nutrition{ 76.0, 0.1, 17.0, 2.2, 2.0, 0.006 };
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

		TEST_METHOD(get_name)
		{
			array<double, 6> nutrition{ 76.0, 0.1, 17.0, 2.2, 2.0, 0.006 };
			Food f("potato", 50, 1000, nutrition);
			Assert::IsTrue("potato" == f.get_name());
		}

		TEST_METHOD(get_price)
		{
			array<double, 6> nutrition{ 76.0, 0.1, 17.0, 2.2, 2.0, 0.006 };
			Food f("potato", 50, 1000, nutrition);
			Assert::AreEqual(50, f.get_price());
		}

		TEST_METHOD(get_weight)
		{
			array<double, 6> nutrition{ 76.0, 0.1, 17.0, 2.2, 2.0, 0.006 };
			Food f("potato", 50, 1000, nutrition);
			Assert::AreEqual(1000, f.get_weight());
		}

		TEST_METHOD(get_kcal_per_100g)
		{
			array<double, 6> nutrition{ 76.0, 0.1, 17.0, 2.2, 2.0, 0.006 };
			Food f("potato", 50, 1000, nutrition);
			Assert::AreEqual(76.0, f.get_kcal_per_100g(), 0.001);
		}

		TEST_METHOD(get_fat_per_100g)
		{
			array<double, 6> nutrition{ 76.0, 0.1, 17.0, 2.2, 2.0, 0.006 };
			Food f("potato", 50, 1000, nutrition);
			Assert::AreEqual(0.1, f.get_fat_per_100g(), 0.001);
		}

		TEST_METHOD(get_carbohydrates_per_100g)
		{
			array<double, 6> nutrition{ 76.0, 0.1, 17.0, 2.2, 2.0, 0.006 };
			Food f("potato", 50, 1000, nutrition);
			Assert::AreEqual(17.0, f.get_carbohydrates_per_100g(), 0.001);
		}

		TEST_METHOD(get_fibre_per_100g)
		{
			array<double, 6> nutrition{ 76.0, 0.1, 17.0, 2.2, 2.0, 0.006 };
			Food f("potato", 50, 1000, nutrition);
			Assert::AreEqual(2.2, f.get_fibre_per_100g(), 0.001);
		}

		TEST_METHOD(get_protein_per_100g)
		{
			array<double, 6> nutrition{ 76.0, 0.1, 17.0, 2.2, 2.0, 0.006 };
			Food f("potato", 50, 1000, nutrition);
			Assert::AreEqual(2.0, f.get_protein_per_100g(), 0.001);
		}

		TEST_METHOD(get_salt_per_100g)
		{
			array<double, 6> nutrition{ 76.0, 0.1, 17.0, 2.2, 2.0, 0.006 };
			Food f("potato", 50, 1000, nutrition);
			Assert::AreEqual(0.006, f.get_salt_per_100g(), 0.001);
		}

		TEST_METHOD(get_kcal)
		{
			array<double, 6> nutrition{ 76.0, 0.1, 17.0, 2.2, 2.0, 0.006 };
			Food f("potato", 50, 1000, nutrition);
			Assert::AreEqual(760.0, f.get_kcal(), 0.001);
		}

		TEST_METHOD(get_fat)
		{
			array<double, 6> nutrition{ 76.0, 0.1, 17.0, 2.2, 2.0, 0.006 };
			Food f("potato", 50, 1000, nutrition);
			Assert::AreEqual(1.0, f.get_fat(), 0.001);
		}

		TEST_METHOD(get_carbohydrates)
		{
			array<double, 6> nutrition{ 76.0, 0.1, 17.0, 2.2, 2.0, 0.006 };
			Food f("potato", 50, 1000, nutrition);
			Assert::AreEqual(170.0, f.get_carbohydrates(), 0.001);
		}

		TEST_METHOD(get_fibre)
		{
			array<double, 6> nutrition{ 76.0, 0.1, 17.0, 2.2, 2.0, 0.006 };
			Food f("potato", 50, 1000, nutrition);
			Assert::AreEqual(22.0, f.get_fibre(), 0.001);
		}

		TEST_METHOD(get_protein)
		{
			array<double, 6> nutrition{ 76.0, 0.1, 17.0, 2.2, 2.0, 0.006 };
			Food f("potato", 50, 1000, nutrition);
			Assert::AreEqual(20.0, f.get_protein(), 0.001);
		}

		TEST_METHOD(get_salt)
		{
			array<double, 6> nutrition{ 76.0, 0.1, 17.0, 2.2, 2.0, 0.006 };
			Food f("potato", 50, 1000, nutrition);
			Assert::AreEqual(0.06, f.get_salt(), 0.001);
		}
	};


	TEST_CLASS(ItemUnitTest)
	{
		TEST_METHOD(Constructor)
		{
			Item i("parasol", 1599, 1);
			Assert::IsTrue("parasol" == i.get_name());
		}

		TEST_METHOD(get_name)
		{
			Item i("parasol", 1599, 1);
			Assert::IsTrue("parasol" == i.get_name());
		}

		TEST_METHOD(get_price)
		{
			Item i("parasol", 1599, 1);
			Assert::AreEqual(1599, i.get_price());
		}

		TEST_METHOD(get_quantity)
		{
			Item i("parasol", 1599, 1);
			Assert::AreEqual(1, i.get_quantity());
		}
	};
}
