/*
MIT License

Copyright (c) 2017 SAE Institute Switzerland AG

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#include <engine/engine.h>
#include <engine/log.h>
#include <python/python_engine.h>
#include <python/pycomponent.h>
#include <engine/game_object.h>
#include <utility/json_utility.h>
#include <memory>
#include <graphics/shape.h>
#include <p2vector.h>

int main()
{
	p2Vec3 a(1.0f, 2.0f, 3.0f);
	p2Vec3 b(4.0f, 5.0f, 6.0f);

	(a + b).Show();
	(a - b).Show();
	std::cout << "Dot product: " << p2Vec3::Dot(a, b) << "\n";
	p2Vec3::Cross(a, b).Show();
	p2Vec3::Lerp(a, b, 0.5f).Show();
	p2Vec3::Proj(a, b).Show();
	p2Vec3::Proj(b, a).Show();
	p2Vec3::Refl(a, b).Show();
	p2Vec3::Refl(b, a).Show();
	std::cout << "Angle between the vectors: " << p2Vec3::AnglesBetween(a, b) << "\n";
	system("pause");
	return 0;

	// Test avec un script
	/*sfge::Engine engine;
	engine.Init(true);

	auto pythonManager = engine.GetPythonManager();

	json gameObjectJson = {
		{ "name", "PyGameObject" },
		{ "components",
		{
			{
				{ "type", (int)sfge::ComponentType::PYCOMPONENT },
				{ "script_path", "scripts/p2vector_test.py" }
			}
		}
		}
	};

	sfge::GameObject* gameObject = sfge::GameObject::LoadGameObject(engine, gameObjectJson);

	for (int i = 0; i < 10; i++)
	{
		sfge::Log::GetInstance()->Msg("GAME OBJECT UPDATE");
		gameObject->Update(sf::seconds(0.4));
	}
	delete(gameObject);
	engine.Destroy();

#ifdef WIN32
	system("pause");
#endif
	return EXIT_SUCCESS;*/
}
