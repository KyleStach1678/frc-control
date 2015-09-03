package org.usfirst.frc.team1678.robot.control;

public interface Filter<T> {
	public T get(T in);
}
