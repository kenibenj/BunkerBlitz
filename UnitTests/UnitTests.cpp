#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MyUnitTestNamespace
{
    TEST_CLASS(MyTestClass)
    {
    public:
        TEST_METHOD(MyTestMethod)
        {
            // Arrange
            int a = 2;
            int b = 3;

            // Act
            int result = a + b;

            // Assert
            Assert::AreEqual(result, 5);
        }
    };
}
