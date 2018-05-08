from SFGE import *


class ContactTest(Component):
    def init(self):
        self.body = self.game_object.get_component(Component.Body)
        self.shape = self.game_object.get_component(Component.Shape)
        self.contact_nmb = 0

    def update(self, dt):
        if self.contact_nmb == 0:
            self.shape.set_fill_color(Color.Red)
        else:
            self.shape.set_fill_color(Color.Green)

        #body.AddForce(p2Vec(2.0, 0.0))

    def on_trigger_enter(self, collider):
        self.contact_nmb += 1
        print("ON TRIGGER ENTER")

    def on_trigger_exit(self, collider):
        self.contact_nmb -= 1
        print("ON TRIGGER EXIT")
