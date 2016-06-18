#!/usr/bin/env ruby

require 'fileutils'

@generated_filename = 'test.in'
@white_p = ARGV[0].to_f

@instance_types = {
  avis_subset_sum: 11,
  avis_knapsack: 12,
  collapsing_knapsack: 13,
  bounded_strongly_correlated: 14,
  no_small_weights: 15
}

@instance_ranges = {
 avis_subset_sum: -> (n) {n*n},
 avis_knapsack: -> (n) {1000},
 collapsing_knapsack: -> (n) {1000},
 bounded_strongly_correlated: -> (n) {1000 * n},
 no_small_weights: -> (n) {1000}
}

@instance_sizes = [50, 100, 500, 1000]

def read_instance(outfile)
  n = 0
  c = 0
  w = Array.new
  p = Array.new

  line_n = 0

  File.open(@generated_filename, 'r').each_line do |line|
    if line_n == 0
      n = line.to_i
    end
  
    if n > 0 && line_n.between?(1,n)
      i, prf, wgt = line.split.map(&:to_i)
      throw "Negative weight: #{wgt}" unless wgt >= 0
      throw "Negative profit: #{prf}" unless prf >= 0
      w << wgt
      p << prf
    end
  
    if n > 0 && line_n == n + 1
      c = line.to_i
      throw "Negative capacity: #{c}" unless c >= 0
      throw "Wrong number of items (p.size = #{p.size}, w.size = #{w.size}, n = #{n})" unless p.size == n and w.size == n
      print_instance(n, c, w, p, outfile)
    end
  
    line_n += 1
  end
end

def print_instance(n, c, w, p, outfile)
  col = Array.new
  n_white = 0
  
  n.times do
    rnd = Random.rand
    col << (rnd < @white_p ? 'b' : 'w')
    n_white += (rnd < @white_p ? 0 : 1)
  end
  
  File.open(outfile, 'w') do |f|
    f.puts "#{n} #{n_white} #{n - n_white} #{c}"
    f.puts col.join(" ")
    f.puts w.join(" ")
    f.puts p.join(" ")
  end
end

def generate_and_translate(id, n, r, type)
  throw "#{@generated_filename} present before executing the generator" if File.file?(@generated_filename)
  throw "Could not execute generator" unless system("./gen #{n} #{r} #{@instance_types[type]} #{id} 1000")
  throw "Generator did not create #{@generated_filename}" unless File.file?(@generated_filename)
  
  outdir = type.to_s
  FileUtils.mkdir_p(outdir) unless File.directory?(outdir)
  outfile = File.join(outdir, "#{id.to_s.rjust(4, '0')}_#{n}_#{r}_col_#{@white_p}.txt")
  
  read_instance(outfile)
  
  File.delete(@generated_filename)
end

def generate_all
  @instance_types.keys.each do |type|
    @instance_sizes.each do |n|
      0.upto(99) do |id|
        puts "*** Generating #{@instance_types[type]}, id = #{id}, n = #{n} ***"
        generate_and_translate(id, n, @instance_ranges[type].call(n), type)
      end
    end
  end
end

generate_all