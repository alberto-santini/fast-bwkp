#!/usr/bin/env ruby

@filename = ARGV[0]
@white_p = ARGV[1].to_f
@generated_instances = 0
@instance_delimiter, @t, @n, @r = File.basename(@filename, '.csv').split('_')
@t = @t.to_i
@n = @n.to_i
@r = @r.to_i

puts "File: #{@filename}"
puts "Instance delimiter: #{@instance_delimiter}, t: #{@t}, n: #{@n}, r: #{@r}"

def print_instance(n, c, z, w, p, x, inst_name)
  throw 'Invalid instance' unless w.size == n and p.size == n and @n == n
  print_random_colour_instance_txt(n, c, z, w, p, x, inst_name)
end

def print_random_colour_instance_txt(n, c, z, w, p, x, instance_name)
  col = Array.new
  n_white = 0
  
  n.times do
    rnd = Random.rand
    col << (rnd < @white_p ? 'b' : 'w')
    n_white += (rnd < @white_p ? 0 : 1)
  end
  
  puts "Writing to file: #{@generated_instances.to_s.rjust(4, '0')}_#{n}_#{@r}_col_#{@white_p}.txt"
  
  File.open("#{@generated_instances.to_s.rjust(4, '0')}_#{n}_#{@r}_col_#{@white_p}.txt", 'w') do |f|
    f.puts "#{n} #{n_white} #{n - n_white} #{c}"
    f.puts col.join(" ")
    f.puts w.join(" ")
    f.puts p.join(" ")
  end
  
  @generated_instances += 1
end

def generate
  in_instance = false
  inst_name = ""
  lines_read = 0
  n = 0
  c = 0
  z = 0
  w = Array.new
  p = Array.new
  x = Array.new
  item_lines = Array.new
  File.open(@filename, 'r').each_line do |line|
    in_instance = true if line.start_with? @instance_delimiter
    next unless in_instance
    lines_read += 1
    case lines_read
    when 1
      n = 0
      c = 0
      z = 0
      w = Array.new
      p = Array.new
      x = Array.new
      item_lines = Array.new
      inst_name = line.strip
    when 2
      s, n = line.split
      n = n.to_i
      item_lines = 6.upto(n+5).to_a
      throw 'Malformed instance: expected n' unless s == 'n'
    when 3
      s, c = line.split
      c = c.to_i
      throw 'Malformed instance: expected c' unless s == 'c'
    when 4
      s, z = line.split
      z = z.to_i
      throw 'Malformed instance: expected z' unless s == 'z'
    when 5
      s = line.split.first
      throw 'Malformed instance: expected time' unless s == 'time'
    when *item_lines
      i, ip, iw, ix = line.split(',')
      throw "Malformed instance: expected i = #{lines_read - 5}, got i = #{i}" unless i.to_i == lines_read - 5
      w << iw.to_i
      p << ip.to_i
      x << ix.to_i
    when item_lines.last + 1
      print_instance(n, c, z, w, p, x, inst_name)
      lines_read = 0
      in_instance = false
    end
  end
end

generate