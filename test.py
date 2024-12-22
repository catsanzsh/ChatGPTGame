from ursina import *

class MyGame(Ursina):
    def __init__(self):
        super().__init__()
        self.setup_environment()
        self.create_player()
        self.setup_mechanics()

    def setup_environment(self):
        """Setup the game environment, including lighting and terrain."""
        self.sky = Sky()
        self.light = DirectionalLight()
        self.light.look_at(Vec3(1, -1, -1))
        self.terrain = Entity(model='plane', scale=64, texture='grass', collider='mesh')

    def create_player(self):
        """Create a controllable player."""
        self.player = Entity(
            model='cube', 
            color=color.orange, 
            position=(0, 1, 0), 
            scale=(1, 2, 1),
            collider='box'
        )
        self.camera_pivot = Entity(parent=self.player, y=1.5)
        camera.parent = self.camera_pivot
        camera.position = (0, 0, -10)
        camera.rotation = (0, 0, 0)

    def setup_mechanics(self):
        """Setup game mechanics such as movement and interactions."""
        self.gravity = 0.05
        self.jump_speed = 0.2
        self.velocity = Vec3(0, 0, 0)

    def update(self):
        """Update the game loop."""
        self.handle_player_movement()

    def handle_player_movement(self):
        """Handle movement mechanics for the player."""
        speed = 5 * time.dt

        # Movement controls
        if held_keys['w']:
            self.player.position += self.player.forward * speed
        if held_keys['s']:
            self.player.position -= self.player.forward * speed
        if held_keys['a']:
            self.player.position -= self.player.right * speed
        if held_keys['d']:
            self.player.position += self.player.right * speed

        # Jump mechanics
        if self.player.y > 1 or held_keys['space']:
            self.velocity.y -= self.gravity
        else:
            self.velocity.y = 0

        if held_keys['space'] and self.player.y <= 1:
            self.velocity.y = self.jump_speed

        self.player.position += self.velocity

if __name__ == '__main__':
    app = MyGame()
    app.run()
