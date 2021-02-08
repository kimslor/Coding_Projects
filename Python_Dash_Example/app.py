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

app = dash.Dash(__name__)

#list used for the axis values
axis_x = [0]
voltage_axis = [0]
current_axis = [0]
temp1_axis = [0]
temp2_axis = [0]
temp3_axis = [0]

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

serial_int("COM2")

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