#!/usr/bin/env ruby

class SlicedInstanceGenerator
  def initialize(n)
    @n = n.to_i
  end
  
  def generate
    w = Array.new
    p = Array.new
    c = Array.new
    
    prng = Random.new
    total_w = 1000000
    avg_w = total_w / @n
    
    0.upto(@n - 1) do |i|
      w[i] = (prng.rand(0.85..1.05) * avg_w).to_i
      p[i] = (prng.rand(0.95..1.0) * w[i]).to_i
      c[i] = (i < @n/2 ? 'b' : 'w')
    end
    
    q = w.inject(0, :+)
    
    0.upto(@n - 1) do |i|
      w[@n + i] = (prng.rand(1.0..1.02) * w[i]).to_i
      p[@n + i] = (prng.rand(1.0..1.02) * p[i] * w[@n + i] / w[i]).to_i
      c[@n + i] = c[i]
    end
    
    num_b = c.count('b')
    num_w = c.count('w')
    
    throw "Invalid number of black and white items" if num_b + num_w != 2 * @n
    
    inst_n = prng.rand(1..10000)
    
    File.open("sliced_#{@n}_#{inst_n}.txt", 'w') do |f|
      f.puts "#{2 * @n} #{num_b} #{num_w} #{q}"
      f.puts c.join(' ')
      f.puts w.join(' ')
      f.puts p.join(' ')
    end
  end
end

i = SlicedInstanceGenerator.new(ARGV[0])
i.generate