   M S B A M L   `   `   `  ���� T  PFresky.UI, Version=2.0.16516.0, Culture=neutral, PublicKeyToken=68c2580f6805686aJ3clr-namespace:Fresky.UI.Controls;assembly=Fresky.UIFresky.UI.Controls  E AMultiMedia, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null'clr-namespace:MultiMedia
MultiMedia    MultiMedia.WinMain   R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35\ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation    R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     @d2http://schemas.microsoft.com/expression/blend/2008     Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     Dctrl3clr-namespace:Fresky.UI.Controls;assembly=Fresky.UI     *localclr-namespace:MultiMedia     -     � Title$  
MainWindow��$	��700��$	��950��$	��680��$	��880��   msMainWindow#��[   � Icon$ Images/icon.ico�� � 	Resources   msHintedTextBox �� 
TargetType �� Property �� Value �� 
TargetType J� Opacity �� RadiusX	 �� RadiusY
 �� CornerRadius ��Name
 J� Uid �� Triggers P� Value P� Property �� 
TargetName  msCommonButton �� 	Resources  Key  BackColorStatic �� Color ��Name  BackBrushStatic �� Stretch :� RoutedEvent �� 
TargetName �� TargetProperty �� From  BackColorOver	 �� To  ThisDuration g� Duration  BackColorDown��%P  &	       &	 �    7  7  7  7  7  7  7  7  7  7  7  7  7  7  �� " ��.���  � �� �� " ��.R�� .+��� 
�������
�������$��3, 3, -3, -3q�$
 0.75Q�$	 2.5��$		 2.5���� 
�������$��1q�$
 3��._�� $��1q�.+��� #��z��$y�Visible=�#��z��#��z��#��z��#��z���� $ tbxHint��#��z $y�Hidden=�#��z��
�������#��z��#��z��#��z�� P�  Z�  � ��. ��� $ tbxHint�� � y�$ Visible=�P�  � ��$  ��. ��� $ tbxHint�� � y�$ Visible=��� " �� ����BackColorStatic 	#FF34BFD0����BackColorOver 	#FF20A8C0����BackColorDown 	#FF2090B0��E�ThisDuration 0:0:0.15D��� BackBrushStatic 8   .���  � ��$ 80����  � ��$ 25����  � �� �	#01FFFFFF��  � ��$ 0q���  � �� �� " ��.R�� .+��� 
�������$��3, 3, -3, -3q�$ 3��$	 3��$	 0.5Q��� $
 rect��8�� $ 5��$	 5���� $��Center=�$��Center=�F� F����        � ��    � �� $� �@��@fр����� �@x}@f�    ��� 	$
��Left=�$	��Top=�$ Uniform=�
�������$
 0.18Q� :� $ UIElement.MouseEnter��.[��� .���� .���� $
 rect��$* $(Shape.Fill).(SolidColorBrush.Color)�8  8  8  :� $ UIElement.MouseLeave��.[��� .���� .���� $
 rect��$* $(Shape.Fill).(SolidColorBrush.Color)�8  8  8  :� $ UIElement.MouseDown��.[��� .���� .���� $
 rect��$* $(Shape.Fill).(SolidColorBrush.Color)�8  8 	 8 
 :� $ UIElement.MouseUp��.[��� .���� .���� $
 rect��$* $(Shape.Fill).(SolidColorBrush.Color)�8  8  8  .��� 
������� � RowDefinitions �� $��25 ��� .+�� -    �Name$ gTitle��
����ح� � ColumnDefinitions �� �� $��25 ��� $��25 ��� $��25 �.+��� $��25��$
��Left=�$��Images/icon.png���� $��30, 0, 0, 0q�$��Center=�$'��!MultiMedia Homework : Image Match��$��14(��� -    ��Name$ spTitle�����	#01FFFFFF�� -    ��Name$ bMini��$��1�����	#01FFFFFF$��0q� 	 msMiniButton#��[	 �� -   $ bMaxi��$��2�����	#01FFFFFF$��0q� 
 msMaxButton#��[
 �� -   $ bClose��$��3�����	#01FFFFFF$��0q�  msCloseButton#��[ � $��1�� �� �� $	��850 ���  �� �� $	��650 ��� .+�� $��1��$��1�� �� $��1 ��� $��31 ��� $��31 ��� .+��� $��Images\bg.jpg��$��4��$��0q��� -   $ tbxSourceFile��$��1��$��3, 3, 90, 3q�$��Center=�$* $Click here to select a pattern image��$�� ��$��13(�#��[ $��0q�.���� -   $ bOpenSourceFile��$��1��$��80��$��3q�$��Right=�$
��Open��#��[ �� -	   $ tbxSourceDir��$��2��$��3, 3, 180, 3q�#��[ $��Center=�  �� 
IsReadOnly  . $4 .Click here to select a search source directory��$�� ��$��13(�$��0q��� -
   $ bOpenSourceDir��$��2��$��80��$��0, 3, 90, 3q�$��Right=�$
��Open��#��[ �� -   $	 bGo��$��2��$��80��$��3q�$��Right=�$	��Go!��#��[ �� 	! �� X1$! 0��	" �� Y1$" 1��	# �� X2$	# 900��	$ �� Y2$$ 1��
�������$��3��$��2��� -   $ gMain��$��3��}�.  �� �� .+��� -   % ��Name$% iSourceFile��$��10q�$��Center=��� $��0��$��10q�$��Source image: ��$��14(��� -   & ��Name$& tbHint��$��100, 5, 0, 0q�$��1��$	��Top=�$��14(��� -   $% imgPreview2��$��1��$
��None=�   Fresky.UI.Controls.Pager  -   '  Name$' 
pgrPreview��$��1��$��20��$��80��$��5q�$
��Left=�$	��Top=�(   Value$( 1��)   EnableMaxHint) . 