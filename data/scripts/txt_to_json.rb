#!/usr/bin/env ruby

require 'json'

n = 0, nb = 0, nw = 0, q = 0
c = Array.new
w = Array.new
p = Array.new

ln = 0
File.open(ARGV[0], 'r').each_line do |l|
  ln += 1

  case ln
  when 1
    n, nb, nw, q = l.split(' ').map(&:to_i)
  when 2
    c = l.split(' ')
  when 3
    w = l.split(' ').map(&:to_i)
  when 4
    p = l.split(' ').map(&:to_i)
  end
end

h = {
  n_items: n,
  capacity: q,
  items: Array.new
}

0.upto(c.size - 1) do |i|
  h[:items] << {
    weight: w[i],
    prize: p[i],
    colour: (c[i] == 'b' ? 1 : -1)
  }
end

File.open(File.basename(ARGV[0], '.txt') + '.json', 'w') do |f|
  f.write(JSON.pretty_generate(h))
end