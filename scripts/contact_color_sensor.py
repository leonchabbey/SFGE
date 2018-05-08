from SFGE import *


class ContactColorSensor(Component):
    def init(self):
        self.shape = self.game_object.get_component(Component.Shape)
        self.contact_nmb = 0

    def update(self, dt):
        if self.contact_nmb == 0:
            self.shape.set_fill_color(Color.White)
        else:
            self.shape.set_fill_color(Color.Blue)

    def on_trigger_enter(self, collider):
        print("test")
        self.contact_nmb += 1

    def on_trigger_exit(self, collider):
        self.contact_nmb -= 1
