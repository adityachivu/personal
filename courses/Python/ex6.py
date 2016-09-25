x = "There are %d types of people." % 10
binary = "binary"
do_not = "don't"
y = "Those who know %s and those who %s." % (binary, do_not) # two are here

print x
print y

print "I said: %r." % x # one more here. the %r places single quotes.
print "I also said: '%s'." % y # another
hilarious = False
joke_evaluation = "Isn't that joke so funny?! %r" # one more here technically. Zed WAS lying.

print joke_evaluation % hilarious
print joke_evaluation + binary # no arg causes formatter to be print as a part of string.

w = "This is the left side of..."
e = "a string with a right side."

print w + e # concatenation.

# This stuff is so bore when you already know a language. But since Zed says we must...