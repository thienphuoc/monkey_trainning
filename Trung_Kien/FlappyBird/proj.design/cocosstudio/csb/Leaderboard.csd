<GameFile>
  <PropertyGroup Name="Leaderboard" Type="Layer" ID="ba581ff8-92b5-4669-9516-245378d87712" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="0" Speed="1.0000" />
      <ObjectData Name="LeaderBoardLayer" Tag="11" ctype="GameLayerObjectData">
        <Size X="1136.0000" Y="768.0000" />
        <Children>
          <AbstractNodeData Name="LeaderBoardBackgroud" ActionTag="2065891232" Tag="14" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" PercentWidthEnable="True" PercentWidthEnabled="True" LeftMargin="153.9849" RightMargin="153.9847" TopMargin="70.0000" BottomMargin="70.0000" LeftEage="273" RightEage="273" TopEage="207" BottomEage="207" Scale9OriginX="273" Scale9OriginY="207" Scale9Width="161" Scale9Height="123" ctype="ImageViewObjectData">
            <Size X="828.0304" Y="628.0000" />
            <Children>
              <AbstractNodeData Name="title" ActionTag="-1348484415" Tag="15" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="45.0152" RightMargin="45.0152" TopMargin="62.8100" BottomMargin="430.1900" LeftEage="243" RightEage="243" TopEage="44" BottomEage="44" Scale9OriginX="243" Scale9OriginY="44" Scale9Width="145" Scale9Height="28" ctype="ImageViewObjectData">
                <Size X="738.0000" Y="135.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="414.0152" Y="497.6900" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="0.7925" />
                <PreSize X="0.8913" Y="0.2150" />
                <FileData Type="Normal" Path="images/leaderboard/leader_board_title.png" Plist="" />
              </AbstractNodeData>
              <AbstractNodeData Name="listViewBackground" ActionTag="2035102374" Tag="11" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" PercentWidthEnable="True" PercentWidthEnabled="True" LeftMargin="183.6797" RightMargin="183.6859" TopMargin="189.0192" BottomMargin="30.9808" TouchEnable="True" LeftEage="208" RightEage="208" TopEage="134" BottomEage="134" Scale9OriginX="208" Scale9OriginY="134" Scale9Width="216" Scale9Height="140" ctype="ImageViewObjectData">
                <Size X="460.6648" Y="408.0000" />
                <Children>
                  <AbstractNodeData Name="ListView_2" ActionTag="1880982921" Tag="21" IconVisible="False" LeftMargin="16.7468" RightMargin="243.9180" TopMargin="179.2155" BottomMargin="28.7845" TouchEnable="True" ClipAble="True" BackColorAlpha="102" ComboBoxIndex="1" ColorAngle="90.0000" IsBounceEnabled="True" ScrollDirectionType="0" ItemMargin="10" DirectionType="Vertical" HorizontalType="Align_HorizontalCenter" ctype="ListViewObjectData">
                    <Size X="200.0000" Y="200.0000" />
                    <Children>
                      <AbstractNodeData Name="temp" ActionTag="-563175531" Alpha="0" Tag="22" IconVisible="False" LeftMargin="5.0000" RightMargin="5.0000" BottomMargin="155.0000" Scale9Enable="True" LeftEage="199" RightEage="199" TopEage="29" BottomEage="29" Scale9OriginX="199" Scale9OriginY="29" Scale9Width="208" Scale9Height="32" ctype="ImageViewObjectData">
                        <Size X="190.0000" Y="45.0000" />
                        <Children>
                          <AbstractNodeData Name="avatar" ActionTag="-1225267243" Tag="23" IconVisible="False" LeftMargin="-22.9569" RightMargin="122.9569" TopMargin="-21.8130" BottomMargin="-23.1870" LeftEage="29" RightEage="29" TopEage="29" BottomEage="29" Scale9OriginX="29" Scale9OriginY="29" Scale9Width="32" Scale9Height="32" ctype="ImageViewObjectData">
                            <Size X="90.0000" Y="90.0000" />
                            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                            <Position X="22.0431" Y="21.8130" />
                            <Scale ScaleX="0.3025" ScaleY="0.4642" />
                            <CColor A="255" R="255" G="255" B="255" />
                            <PrePosition X="0.1160" Y="0.4847" />
                            <PreSize X="0.4737" Y="2.0000" />
                            <FileData Type="Normal" Path="images/leaderboard/avatar.png" Plist="" />
                          </AbstractNodeData>
                          <AbstractNodeData Name="name" ActionTag="-1020750093" Tag="24" IconVisible="False" PositionPercentYEnabled="True" LeftMargin="54.5948" RightMargin="95.4052" TopMargin="13.4886" BottomMargin="13.5114" FontSize="15" LabelText="name" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                            <Size X="40.0000" Y="18.0000" />
                            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                            <Position X="74.5948" Y="22.5114" />
                            <Scale ScaleX="0.5383" ScaleY="1.3643" />
                            <CColor A="255" R="90" G="130" B="33" />
                            <PrePosition X="0.3926" Y="0.5003" />
                            <PreSize X="0.2105" Y="0.4000" />
                            <FontResource Type="Normal" Path="fonts/Roboto-Bold.ttf" Plist="" />
                            <OutlineColor A="255" R="255" G="0" B="0" />
                            <ShadowColor A="255" R="110" G="110" B="110" />
                          </AbstractNodeData>
                          <AbstractNodeData Name="score" ActionTag="1941910274" Tag="25" IconVisible="False" PositionPercentYEnabled="True" LeftMargin="134.4840" RightMargin="15.5160" TopMargin="13.5000" BottomMargin="13.5000" FontSize="15" LabelText="score" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                            <Size X="40.0000" Y="18.0000" />
                            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                            <Position X="154.4840" Y="22.5000" />
                            <Scale ScaleX="0.6306" ScaleY="1.3643" />
                            <CColor A="255" R="90" G="130" B="33" />
                            <PrePosition X="0.8131" Y="0.5000" />
                            <PreSize X="0.2105" Y="0.4000" />
                            <FontResource Type="Normal" Path="fonts/Roboto-Bold.ttf" Plist="" />
                            <OutlineColor A="255" R="255" G="0" B="0" />
                            <ShadowColor A="255" R="110" G="110" B="110" />
                          </AbstractNodeData>
                        </Children>
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="100.0000" Y="177.5000" />
                        <Scale ScaleX="1.0000" ScaleY="1.0000" />
                        <CColor A="255" R="255" G="255" B="255" />
                        <PrePosition X="0.5000" Y="0.8875" />
                        <PreSize X="0.9500" Y="0.2250" />
                        <FileData Type="Normal" Path="images/leaderboard/item_bg.png" Plist="" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint />
                    <Position X="16.7468" Y="28.7845" />
                    <Scale ScaleX="2.1414" ScaleY="1.7580" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.0364" Y="0.0706" />
                    <PreSize X="0.4342" Y="0.4902" />
                    <SingleColor A="255" R="150" G="150" B="255" />
                    <FirstColor A="255" R="150" G="150" B="255" />
                    <EndColor A="255" R="255" G="255" B="255" />
                    <ColorVector ScaleY="1.0000" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="414.0121" Y="234.9808" />
                <Scale ScaleX="1.7556" ScaleY="0.9956" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="0.3742" />
                <PreSize X="0.5563" Y="0.6497" />
                <FileData Type="Normal" Path="images/leaderboard/list_view_bg.png" Plist="" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="568.0001" Y="384.0000" />
            <Scale ScaleX="1.3286" ScaleY="1.2056" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5000" Y="0.5000" />
            <PreSize X="0.7289" Y="0.8177" />
            <FileData Type="Normal" Path="images/leaderboard/leader_board_bg.png" Plist="" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameFile>