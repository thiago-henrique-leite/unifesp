# frozen_string_literal: true

# Traveling Salesman Problem (TSP) using PSO
class TravelingSalesmanProblemWithPSO
  ITERATIONS = 200
  PARTICLE_SIZE = 8
  PARTICLES_SIZE = 50

  DISTANCES = {
    'AB' => 42,
    'AC' => 61,
    'AD' => 30,
    'AE' => 17,
    'AF' => 82,
    'AG' => 31,
    'AH' => 11,
    'BC' => 14,
    'BD' => 87,
    'BE' => 28,
    'BF' => 70,
    'BG' => 19,
    'BH' => 33,
    'CD' => 20,
    'CE' => 81,
    'CF' => 21,
    'CG' => 8,
    'CH' => 29,
    'DE' => 34,
    'DF' => 33,
    'DG' => 91,
    'DH' => 10,
    'EF' => 41,
    'EG' => 34,
    'EH' => 82,
    'FG' => 19,
    'FH' => 32,
    'GH' => 59
  }.freeze

  attr_reader :particles, :best_speed_to_particles, :bestest_particle

  def initialize
    @particles = []
    @best_speed_to_particles = {}
  end

  def self.perform
    new.perform
  end

  def perform
    generate_particles

    ITERATIONS.times do
      update_particles
      update_local_best
      update_global_best
    end

    bestest_particle
  end

  private

  def generate_particles
    base_particle = %w[A B C D E F G H]

    PARTICLES_SIZE.times do
      @particles << format_particle(base_particle.shuffle)
    end

    update_local_best
    update_global_best
  end

  def format_particle(particle)
    rotated_particle = particle.dup
    rotated_particle << rotated_particle.shift

    particle.zip(rotated_particle).map(&:sort).map(&:join)
  end

  def velocity(particle)
    particle.sum { |trip| DISTANCES[trip] }
  end

  def update_local_best
    particles.each do |particle|
      particle_velocity = velocity(particle)

      next unless best_speed_to_particles[particle].nil? || particle_velocity < best_speed_to_particles[particle]

      @best_speed_to_particles[particle] = particle_velocity
    end
  end

  def update_global_best
    candidate = best_speed_to_particles.min_by { |_, v| v }

    return unless bestest_particle.nil? || candidate[1] < bestest_particle[1]

    @bestest_particle = candidate
    @bestest_particle.first.sort!
  end

  def update_particles
    particles.each_with_index do |particle, index|
      items = particle.join.chars.uniq

      particles[index] = update_particle_items(items)
    end
  end

  def update_particle_items(items)
    swap(items, rand_index, rand_index)
    swap(items, rand_index, rand_index)

    format_particle(items)
  end

  def swap(items, index1, index2)
    aux = items[index1]

    items[index1] = items[index2]
    items[index2] = aux
  end

  def rand_index
    rand(0...PARTICLE_SIZE)
  end
end

TravelingSalesmanProblemWithPSO.perform
