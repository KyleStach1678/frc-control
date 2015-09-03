package org.usfirst.frc.team1678.robot.control;

import java.util.Vector;

@SuppressWarnings("rawtypes")
public class ControlUpdater {
	public static Vector<Controller> controllers = new Vector<Controller>();

	public static void addController(Controller controller) {
		controllers.addElement(controller);
	}

	public static void update() {
		double dt = .05;
		synchronized (controllers) {
			for (Controller c : controllers) {
				c.update(dt);
			}
		}
	}
}
