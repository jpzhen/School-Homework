class Machine(object):
    def __init__(self, name):
        self._name = name
        self._header = ""
        self._footer = ""
        self._edges = []
        self._states = []
        self._uniqEvent = set()

    #use by state to get the edges
    def edge(self,name, next_state, action_string=''):
        self._edges.append((name, next_state, action_string))
        self._uniqEvent.add(name)
        return self._edges[-1]

    #use a state with multple edges
    def edges(self, *argv):
        arr = []
        for arg in argv:
            arr.append(self.edge(arg[0], arg[1]))
        return arr

    #store the name of the state, the action to get to next state, tuple of next [event, state] 
    def state(self, name, action, edges = None):
        if edges is None:
            edges = []
        self._states.append((name, action, edges))

    def header(self, text):
        self._header = text

    def footer(self, text):
        self._footer = text

    def print_enum_states(self):
        print("enum State {")
        for i, state in enumerate(self._states):
            if (i != len(self._states) - 1):
                print("   ", state[0]+"_STATE,")
            else:
                print("   ", state[0]+"_STATE")
        print("};")

    def printStringToEvent(self):
        print('Event string_to_event(string event_string) {')
        for e in self._uniqEvent:
            print('  if (event_string == "%s") {return %s;}' % (e, e+'_EVENT'))
        print('  return INVALID_EVENT;\n}')

    def print_enum_edges(self):
        print("enum Event {")
        for e in self._uniqEvent:
            print("   ",e+"_EVENT,")
        s = "INVALID_EVENT"
        print("   ",s)
        print("};")

    def print_eventNames(self):
        print("const char * EVENT_NAMES[] = {")
        for i, e in enumerate(self._uniqEvent):
            if (i != len(self._uniqEvent) - 1):
                print("    \""+e+"\",")
            else:
                print("    \""+e+"\"")
        print("};")

    def print_event(self, event):
        print("        case ", event[0]+"_EVENT:")
        print("        ",event[2])
        print("                state =", event[1]+"_STATE;")
        print("                break;")

    def print_state(self, state):
        print(("      case %s:") % (state[0]+"_STATE"))
        print(("         cerr << \"state %s\" << endl;") % (state[0]))
        print("            ",state[1])
        print("        event = get_next_event();")
        print("        cerr << \"event \" << EVENT_NAMES[event] << endl;")
        print("        switch(event) {")
        for e in state[2]:
            self.print_event(e)
        
        print("        default:")
        print(("                cerr << \"INVALID EVENT \" << event << \" in state %s\" << endl;") % (state[0]))
        print("                return -1;")
        print("        }")
        print("        break;")

    def print_body(self):
        print("Event get_next_event();")
        print()
        self.printStringToEvent()
        print(("int %s(State initial_state) {") % (self._name))
        print("  State state = initial_state;")
        print("  Event event;")
        print("  while (true) {")
        print("     switch (state) {")

        for state in self._states:
            self.print_state(state)

        print("     }")
        print("   }")
        print("}")

    def gen(self):
        print(self._header)
        self.print_enum_states()
        self.print_enum_edges()
        self.print_eventNames()
        self.print_body()
        print(self._footer)