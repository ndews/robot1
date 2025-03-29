
// WALL·E Style Desktop Robot Shell (OpenSCAD)
// Dimensions: 100 x 60 x 50 mm body
// With slots for: ESP32, TFT, Speaker, Mic, Servo arms

module robot_shell() {
    difference() {
        // Outer shell
        cube([100, 60, 50], center = false);

        // TFT display cutout (front)
        translate([30, 58, 10])
            cube([40, 3, 30]);

        // ESP32 slot (rear)
        translate([32.5, -3, 10])
            cube([35, 3, 20]);

        // Speaker cutout (front center low)
        translate([42.5, 5, 0])
            cube([15, 15, 10]);

        // Left arm servo mount
        translate([-10, 25, 25])
            cube([10, 10, 10]);

        // Right arm servo mount
        translate([100, 25, 25])
            cube([10, 10, 10]);

        // Screw holes (corners)
        for (x=[3, 97]) for (y=[3, 57])
            translate([x, y, 0])
                cylinder(h=5, r=1.5, $fn=30);
    }
}

robot_shell();
