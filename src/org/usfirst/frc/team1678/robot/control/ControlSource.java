package org.usfirst.frc.team1678.robot.control;

import org.usfirst.frc.team1678.robot.math.Matrix;

import edu.wpi.first.wpilibj.Encoder;

/**
 * An interface to be implemented by sensors used in controllers.
 * 
 * @author Kyle
 * @param <T>
 *            The variable type that the sensor returns.
 */
public interface ControlSource<T> {
	/**
	 * An encoder sensor
	 * 
	 * @author Kyle
	 *
	 */
	public class EncoderControlSource implements ControlSource<Double> {
		private Encoder enc;
		double zeroVal;

		public EncoderControlSource(Encoder enc) {
			this.enc = enc;
			zeroVal = enc.get();
		}

		@Override
		public Double read() {
			return (double) enc.get() - zeroVal;
		}

		public void reset() {
			zeroVal += read();
		}
	}

	/**
	 * A group of sensors, each returning a separate value
	 * 
	 * @author Kyle
	 *
	 */
	public class VectorControlSource implements ControlSource<Matrix> {
		private ControlSource<Double> sources[];

		public VectorControlSource(ControlSource<Double> sources[]) {
			this.sources = sources;
		}

		@Override
		public Matrix read() {
			Matrix values = new Matrix(sources.length);
			for (int i = 0; i < sources.length; i++) {
				values.setValue(sources[i].read(), i, 0);
			}
			return values;
		}

		@SafeVarargs
		public static VectorControlSource makeMultiCS(ControlSource<Double>... sources) {
			return new VectorControlSource(sources);
		}
	}

	/**
	 * A source that gets run through a filter
	 * 
	 * @author Kyle
	 *
	 * @param <T>
	 */
	public class FilteredControlSource<T> implements ControlSource<T> {
		ControlSource<T> source;
		Filter<T> filter;

		public FilteredControlSource(Filter<T> filter, ControlSource<T> source) {
			this.filter = filter;
			this.source = source;
		}

		@Override
		public T read() {
			return filter.get(source.read());
		}
	}

	/**
	 * This should be implemented to get the value from the sensor
	 * 
	 * @return The value from the sensor
	 */
	public T read();

	/**
	 * Filter the source using an implementation of Filter
	 * 
	 * @param filter
	 *            The filter to use
	 * @return A FilteredControlSource that filters this sensor's output through
	 *         the filter
	 */
	public default ControlSource<T> filter(Filter<T> filter) {
		return new FilteredControlSource<T>(filter, this);
	}
}