class LinearRegression 

  attr_reader :x_values, :y_values, :x_average, :y_average, :coefficient_a, :coefficient_b

  def initialize(x_values, y_values)
    @x_values = x_values
    @y_values = y_values
  end

  def self.perform(*args)
    new(*args).perform
  end

  def perform
    calculate_averages
    calculate_coeficient_b
    calculate_coeficient_a
    print_generated_function
  end

  private

  def calculate_averages
    @x_average = average(x_values)
    @y_average = average(y_values)
  end

  def calculate_coeficient_a
    @coefficient_a = (y_average - (coefficient_b * x_average)).round(4)
  end

  def calculate_coeficient_b
    summation_a, summation_b = 0, 0

    x_values.size.times do |i|
      summation_a += x_values[i] * (y_values[i] - y_average)
      summation_b += x_values[i] * (x_values[i] - x_average)
    end

    @coefficient_b = (summation_a.to_f / summation_b.to_f).round(4)
  end

  def average(array)
    soma_total = 0
    array.each{ |n| soma_total += n }
    soma_total.to_f / array.size
  end

  def print_generated_function
    puts ""
    puts "\t Valores X: #{x_values.inspect}"
    puts "\t Valores Y: #{y_values.inspect}"
    puts ""
    puts "\t Função: y = #{coefficient_b} x + #{coefficient_a}"
    puts ""
  end
end

x_values = [139, 126, 90, 144, 163, 136, 61, 62, 41, 120];
y_values = [122, 114, 86, 134, 146, 107, 68, 117, 71, 98];

LinearRegression.perform(x_values, y_values)

x_values = [907, 926, 506, 741, 789, 889, 874, 510, 529, 420, 679, 872, 924, 607, 452, 729, 794, 844, 1010, 621];
y_values = [11.20, 11.05, 6.84, 9.21, 9.42, 10.08, 9.45, 6.73, 7.24, 6.12, 7.63, 9.43, 9.46, 7.64, 6.92, 8.95, 9.33, 10.23, 11.77, 7.41];

LinearRegression.perform(x_values, y_values)
