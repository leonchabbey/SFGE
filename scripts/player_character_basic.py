from SFGE import *

class PlayerCharacterBasic(Component):

    def init(self):
        self.speed = 3.0
        self.body = self.game_object.get_component(Component.Body)

    def update(self, dt):
        d = p2Vec2(0.0,0.0)
        if input_manager.keyboard.is_key_held(KeyboardManager.Key.Up):
            d.y -= 1
        if input_manager.keyboard.is_key_held(KeyboardManager.Key.Down):
            d.y += 1
        if input_manager.keyboard.is_key_held(KeyboardManager.Key.Left):
            d.x -= 1
        if input_manager.keyboard.is_key_held(KeyboardManager.Key.Right):
            d.x += 1

        d *= self.speed
        self.body.velocity = d

        print("velocity.x :" + str(self.body.velocity.x))
        print("velocity.y :" + str(self.body.velocity.y))

    def on_trigger_enter(self, collider):
        pass

    def on_trigger_exit(self, collider):
        pass
