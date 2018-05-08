from SFGE import *


class ContactColorSensor(Component):
    def init(self):
        self.body = self.game_object.get_component(Component.Body)
        self.shape = self.game_object.get_component(Component.Shape)
        self.contact_nmb = 0
        self.body.velocity = p2Vec2(1.0, 1.0)

    def update(self, dt):
        if self.contact_nmb == 0:
            self.shape.set_fill_color(Color.White)
        else:
            self.shape.set_fill_color(Color.Blue)

    def on_trigger_enter(self, collider):
        self.contact_nmb += 1

    def on_trigger_exit(self, collider):
        self.contact_nmb -= 1
