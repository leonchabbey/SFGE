from SFGE import *


class ContactColor(Component):
    def init(self):
        self.body = self.game_object.get_component(Component.Body)
        self.shape = self.game_object.get_component(Component.Shape)
        self.contact_nmb = 0

    def update(self, dt):
        if self.contact_nmb == 0:
            self.shape.set_fill_color(Color.Red)
        else:
            self.shape.set_fill_color(Color.Green)

    def on_collision_enter(self, collider):
        self.contact_nmb += 1

    def on_collision_exit(self, collider):
        self.contact_nmb -= 1
