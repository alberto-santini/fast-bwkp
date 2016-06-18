#!/usr/bin/env ruby

class HardInstanceGenerator
  def initialize(n)
    @n = n.to_i
  end
  
  def generate
    weights = Array.new
    profits = Array.new
    colours = Array.new
    
    prng = Random.new
    
    1.upto(@n/2) do |i|
      w = prng.rand(1..1000)
      p = prng.rand(w..(w+100))
      weights << w
      profits << p
      colours << 'b'
    end
    
    (@n/2 + 1).upto(@n) do |i|
      w = prng.rand(5000..10000)
      p = prng.rand((w - 1000)..w)
      weights << w
      profits << p
      colours << 'b'
    end
    
    1.upto(@n/2) do |i|
      weights << prng.rand(1..10000)
      profits << prng.rand(1..10000)
      colours << 'w'
    end
    
    a = prng.rand(0.9..1.1)
    q = weights[(@n/2)..-1].inject(0, :+) * a
    
    inst_n = prng.rand(1..10000)
    
    File.open("difficult_#{@n}_#{inst_n}.txt", 'w') do |f|
      f.puts "#{@n + @n/2} #{@n} #{@n/2} #{q.to_i}"
      f.puts colours.join(' ')
      f.puts weights.join(' ')
      f.puts profits.join(' ')
    end
  end
end

i = HardInstanceGenerator.new(ARGV[0])
i.generate