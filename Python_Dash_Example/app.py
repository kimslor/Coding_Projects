import serial
import random
import time
import dash
import dash_core_components as dcc
import dash_html_components as html
import pandas as pd
import plotly.express as px
import plotly.graph_objects as go
from dash.dependencies import Output, Input
from plotly.subplots import make_subplots

#heroku creation + add on FREE postgres database, get/store access information 
#psycopg2 library on python, establish connection w/ database, create first table (can be easily deleted later), commit changes, and read (i.e., select) values off table
#long term: figure out data storage method (i.e., from reading a com port to online database (how do you want your data organized)), (local script) + create online script that reads from database and updates plotly/dash page
#most important: html/css for aesthetics

app = dash.Dash(__name__)

#list used for the axis values
axis_x = [0]
voltage_axis = [0]
current_axis = [0]
temp1_axis = [0]
temp2_axis = [0]
temp3_axis = [0]

#checks the first word of string to see if it is a measurement line
def data_selector(string):
    switcher = {
        "TEMP1": True
        "TEMP2": True
        "TEMP3": True
        "ISENS": True
        "VSENS": True
    }
    return switcher.get(string, False) #returns false if it is not a measurement line

def parse_str(port):
    output = [0]
    line = port.readline()
    collapsed_line = ' '.join(line.split()) #merge all the consective white spaces
    split_string = collapsed_line.split(' ') #split into list of strings
    if data_selector(split_string[0]):
        output.append(split_string[0]) #data type/channel
        output.append(split_string[1]) #data value
        return output

#serial initalisation
def serial_int(id_port):
    p = None

    try: 
        p = serial.Serial(
            port = id_port,
            baudrate = 9600,
            bytesize = serial.EIGHTBITS,
            parity = serial.PARITY_NONE,
            stopbits = serial.STOPBITS_ONE,
        )

    except serial.SerialException as msg:
        print("Failed to open port: {0}".format(msg))

    return p

port = serial_int("COM2") #port selection

#page layout
app.layout = html.Div([
    dcc.Graph(
        id = 'graph',
        animate = False
    ),
    dcc.Interval(
        id = 'timer',
        interval = 1000, #1s intervals
        n_intervals = 0
    )
])

# Add traces
@app.callback(Output('graph', 'figure'),
              Input('timer', 'n_intervals'))
def update_figure(self):
    #increment time axis_x
    axis_x.append(axis_x[-1] + 1)

    #add new values to the lists
    new_values = parse_str(port)

    voltage_axis.append(random.randint(0,10))
    current_axis.append(random.randint(0,10))
    temp1_axis.append(random.randint(0,10))
    temp2_axis.append(random.randint(0,10))
    temp3_axis.append(random.randint(0,10))

    fig = make_subplots(
        rows = 2, cols = 3,
        horizontal_spacing = 0.1,
        #vertical_spacing = 0.25,
        subplot_titles = ("Temp1", "Temp2", "Temp3", "Voltage", "Current")
    )

    fig.update_layout(shapes=[
        # adds line at y=Rated_V
        {'type': 'line','y0':8,'y1': 8,'x0':-20, 
            'x1':axis_x[-1]+10,'xref':'x1','yref':'y1',
            'line': {'color': 'red','width': 2.5}
        },
        {'type': 'line','y0':8,'y1': 8,'x0':-20, 
            'x1':axis_x[-1]+10,'xref':'x2','yref':'y2',
            'line': {'color': 'red','width': 2.5}
        },
        {'type': 'line','y0':8,'y1': 8,'x0':-20, 
            'x1':axis_x[-1]+10,'xref':'x3','yref':'y3',
            'line': {'color': 'red','width': 2.5}
        },
        {'type': 'line','y0':8,'y1': 8,'x0':-20, 
            'x1':axis_x[-1]+10,'xref':'x4','yref':'y4',
            'line': {'color': 'red','width': 2.5}
        },
        {'type': 'line','y0':8,'y1': 8,'x0':-20, 
            'x1':axis_x[-1]+10,'xref':'x5','yref':'y5',
            'line': {'color': 'red','width': 2.5}
        }
    ])

    fig.add_trace(
        go.Scatter(
            x=list(axis_x), 
            y=list(temp1_axis), 
            mode='lines+markers', 
            name='Temp1'
        ),
        row = 1, col = 1,
    )
    fig.add_trace(
        go.Scatter(
            x=list(axis_x), 
            y=list(temp2_axis), 
            mode='lines+markers', 
            name='Temp2'
        ),
        row = 1, col = 2,
    )
    fig.add_trace(
        go.Scatter(
            x=list(axis_x), 
            y=list(temp3_axis), 
            mode='lines+markers', 
            name='Temp3'
        ),
        row = 1, col = 3,
    )
    fig.add_trace(
        go.Scatter(
            x=list(axis_x), 
            y=list(voltage_axis), 
            mode='lines+markers', 
            name='Voltage'
        ),
        row = 2, col = 1,
    )
    fig.add_trace(
        go.Scatter(
            x=list(axis_x), 
            y=list(current_axis), 
            mode='lines+markers', 
            name='Current'
        ),
        row = 2, col = 2,
    )

    #updating axis ranges
    fig.update_xaxes(title_text = "time(s)", range = [axis_x[-1]-20, axis_x[-1]+10], row = 1, col = 1)
    fig.update_xaxes(title_text = "time(s)", range = [axis_x[-1]-20, axis_x[-1]+10], row = 2, col = 1)
    fig.update_xaxes(title_text = "time(s)", range = [axis_x[-1]-20, axis_x[-1]+10], row = 1, col = 2)
    fig.update_xaxes(title_text = "time(s)", range = [axis_x[-1]-20, axis_x[-1]+10], row = 2, col = 2)
    fig.update_xaxes(title_text = "time(s)", range = [axis_x[-1]-20, axis_x[-1]+10], row = 1, col = 3)

    fig.update_yaxes(title_text = "Temp1(*C)", range = [0, 10], row = 1, col = 1)
    fig.update_yaxes(title_text = "Temp2(*C)", range = [0, 10], row = 1, col = 2) 
    fig.update_yaxes(title_text = "Temp3(*C)", range = [0, 10], row = 1, col = 3)
    fig.update_yaxes(title_text = "Voltage(mV)", range = [0, 10], row = 2, col = 1)
    fig.update_yaxes(title_text = "Current(mA)", range = [0, 10], row = 2, col = 2)

    fig.update_layout(height = 500, width = 1000)

    return fig



if __name__ == '__main__':
    app.run_server(debug=True)