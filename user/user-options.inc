# Example of a user option

config	CONFIG_EXAMPLES
	bool	"Examples"

config	CONFIG_EXAMPLES_VAR
	depends	on CONFIG_EXAMPLES
	string	"examples	--enable-<var>"
	default	"examples"
