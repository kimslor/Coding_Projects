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
time_x = [0]
random_y = [0]

app.layout = html.Div([
    dcc.Graph(
        id = 'graph',
        animate = True
    ),
    dcc.Interval(
        id = 'timer',
        interval = 500,
        n_intervals = 0
    )
])

# Add traces
@app.callback(Output('graph', 'figure'),
              Input('timer', 'n_intervals'))
def update_figure(self):
    time_x.append(time_x[-1] + 1)
    random_y.append(random_y[-1] + 1)

    fig = make_subplots(
        rows = 2, cols = 2,
        subplot_titles = ("Voltage for Temp1", "Voltage for Temp2", "Voltage for Temp3")
    )

    fig.add_trace(
        go.Scatter(
            x=list(time_x), 
            y=list(random_y), 
            mode='lines+markers', 
            name='Temp1'
        ),
        row = 1, col = 1,
    )
    fig.add_trace(
        go.Scatter(
            x=list(time_x), 
            y=list(random_y), 
            mode='lines+markers', 
            name='Temp2'
        ),
        row = 2, col = 1,
    )
    fig.add_trace(
        go.Scatter(
            x=list(time_x), 
            y=list(random_y), 
            mode='lines+markers', 
            name='Temp3'
        ),
        row = 1, col = 2,
    )

    fig.update_xaxes(title_text = "time(s)", range = [0, 10], row = 1, col = 1)
    fig.update_xaxes(title_text = "time(s)", range = [0, 10], row = 2, col = 1)
    fig.update_xaxes(title_text = "time(s)", range = [0, 10], row = 1, col = 2)

    fig.update_yaxes(title_text = "Temp1(mV)", range = [0, 10], row = 1, col = 1)
    fig.update_yaxes(title_text = "Temp2(mV)", range = [0, 10], row = 2, col = 1)
    fig.update_yaxes(title_text = "Temp3(mV)", range = [0, 10], row = 1, col = 2)

    fig.update_layout(height = 700, width = 1200)

    return fig



if __name__ == '__main__':
    app.run_server(debug=True)