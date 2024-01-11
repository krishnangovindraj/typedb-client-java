using NUnit.Framework;


namespace TypeDB.BDD.Steps {

   [TestFixture]
    public class HelloSteps
    {
        [SetUp]
        public void SetUp()
        {
        }

        [Test]
        public void SayHello()
        {
            TypeDB.HelloLib.SayHello("Test");
        }
    }
}
