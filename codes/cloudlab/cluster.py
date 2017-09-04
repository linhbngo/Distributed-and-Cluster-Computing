import geni.portal as portal
import geni.rspec.pg as rspec
import geni.rspec.igext as IG

pc = portal.Context()
request = rspec.Request()

pc.defineParameter("workerCount",
                   "Number of computing nodes",
                   portal.ParameterType.INTEGER, 3)

pc.defineParameter("controllerHost", "Name of head node",
                   portal.ParameterType.STRING, "node0", advanced=True,
                   longDescription="The short name of the master node. You shold leave this alone unless you really want the hostname to change.")

params = pc.bindParameters()

tourDescription = "This profile provides a configurable cluster with one master running Apache and customizable computing nodes."

tourInstructions = \
  """
### Basic Instructions
Once your experiment nodes have booted, and this profile's configuration scripts have finished deploying, you'll be able to visit [the Apache Webserver interface](http://{host-%s}) on the master node. All  
""" % (params.controllerHost)

#
# Setup the Tour info with the above description and instructions.
#  
tour = IG.Tour()
tour.Description(IG.Tour.TEXT,tourDescription)
tour.Instructions(IG.Tour.MARKDOWN,tourInstructions)
request.addTour(tour)


# Create a Request object to start building the RSpec.
#request = portal.context.makeRequestRSpec()
#request 
# Create a link with type LAN
link = request.LAN("lan")

# Generate the nodes
for i in range(params.workerCount + 1):
    node = request.RawPC("node" + str(i))
    node.disk_image = "urn:publicid:IDN+emulab.net+image+emulab-ops:UBUNTU14-64-STD"
    iface = node.addInterface("if" + str(i))
    iface.component_id = "eth1"
    iface.addAddress(rspec.IPv4Address("192.168.1." + str(i + 1), "255.255.255.0"))
    link.addInterface(iface)

    if i == 0:
        node.addService(rspec.Execute(shell="/bin/sh",
                                      command="sudo apt-get update"))
        node.addService(rspec.Execute(shell="/bin/sh",
                                      command="sudo apt-get install -y apache2"))

# Print the RSpec to the enclosing page.
portal.context.printRequestRSpec(request)